#include <stdio.h>
#include "touch.h"
#include "lcd.h"
#include "bmp.h"
#include "filelist.h"
#include "fun.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <linux/input.h>	//输入子系统的头文件
#include <sys/mman.h>	



/*
    show_bmps：电子相册
    根据手指的上下左右滑动播放图片
*/
void show_bmps()
{
	DoubleCircleList*l = create_PictureList();
    show_bmp(0,0,l->first->filename);
	int way;
    int x,y;
	while(1)
	{
		way = get_fingle_move();
		if (way == 1 || way == 3)
        {
            show_bmp(0,0,l->first->filename);
            l->first = l->first->next;
        }
        if (way == 2 || way == 4)
        {
            show_bmp(0,0,l->first->filename);
            l->first = l->first->prev;
        }
        if(way == 0)
        {
            show_bmp(0,0,"2.bmp");
            get_user_touch(&x,&y);
            if ((x > 300 && x < 350) && (y > 280 && y < 320))
            {
                show_bmp(0,0,l->first->filename);
                continue;
            }
            if ((x > 470 && x < 540) && (y > 280 && y < 320))
            {
                show_bmp(0,0,"start.bmp");
                break;
            }
        }

	}
}

/*
    播放音乐
*/
void* play_music(void* arg)
{
    char buf[256] = {0};
    sprintf(buf,"madplay %s &",(char*)arg);
    printf("%s\n",buf);
    system(buf);
    int x,y;
    while(1)
    {
        get_user_touch(&x,&y);
        if (x > 460 && x < 520 && y > 360 && y < 410)
        {
            system("killall -STOP madplay");
        }
        if (x > 460 && x < 520 && y > 420 && y < 480)
        {
            system("killall -CONT madplay");
        }
        if (x > 750 && x < 800 && y > 0 && y < 50)
        {
            system("killall -9 madplay");
            break;
        }
        
    }
}
/* 
    播放视频
 */
void play_video(char* name)
{
    char buf[256] = {0};
    sprintf(buf,"mplayer -slave -quiet -geometry 0:0 -zoom -x 800 -y 480 %s &",name);
    system(buf);
}


/*多进程编程实现音乐播放器*/
void play_musics()
{
	int i = 0;
    int k = 0;
    int x,y;
	pid_t pid;

    /*
    creat_Musiclist:创建一个带头结点的循环双向音乐链表
    */
    DoubleCircleList*l = create_MusicList();

	//char music_path[3][32] = {"1.mp3", "2.mp3", "3.mp3"};
	//1, 显示音乐播放器界面  --> 播放,暂停,继续，上一曲,下一曲,结束,退出
	//2, 等待用户点击屏幕
	while(1)
	{
		get_user_touch(&x,&y);		//获取用户点击的坐标
		if(x > 460 && x < 520 && y > 320 && y < 360)	//如果点击播放音乐	--> 创建一条子进程播放音乐 
		{
			pid = fork();	//子进程
			if(pid == 0)	//子进程执行部分-->播放下标为i的音乐
			{
				execl("/usr/bin/madplay", "madplay",l->first->filename, NULL);
			}
		}
		if(x > 460 && x < 520 && y > 360 && y < 410 && k==0)	//点击暂停 --> 发信号
		{

			k=1;
			kill(pid, SIGSTOP);	
			printf("madplay STOP!\n");
			sleep(1);
		}
		if(x > 460 && x < 520 && y > 420 && y < 480 && k==1)	//点击继续 --> 发信号
		{
			kill(pid, SIGCONT);	
			printf("madplay CONT!\n");
			k=0;
		}
        //列表循环播放(父进程使用wait), 播放下一首。
		if(x > 540 && x < 580 && y > 420 && y < 480)	//点击下一首
		{
			//结束当前这一首,然后播放下一首
			kill(pid, SIGKILL);
            l->first = l->first->next;
			i--;
			if(i < 0)
				i = 2;
			
			pid = fork();	//子进程
			if(pid == 0)	//子进程执行部分-->播放下标为i的音乐
			{
				execl("/usr/bin/madplay", "madplay", l->first->filename, NULL);
			}			
		}

        //列表循环播放(父进程使用wait), 播放上一首。
		if(x > 400 && x < 440 && y > 420 && y < 480)	//点击上一首
		{
			//结束当前这一首,然后播放上一首
			kill(pid, SIGKILL);
            l->first = l->first->prev;
			i++;
			if(i >2)
				i = 0;
			
			pid = fork();	//子进程
			if(pid == 0)	//子进程执行部分-->播放下标为i的音乐
			{
				execl("/usr/bin/madplay", "madplay",l->first->filename, NULL);
			}						
		}

        if (x > 750 && x < 800 && y > 0 && y < 50)
        {
            show_bmp(0,0,"1.bmp");
            get_user_touch(&x,&y);
            if ((x > 610 && x < 650) && (y > 110 && y < 150))
            {
                show_bmp(0,0,"music.bmp");
                continue;
            }
            if ((x > 510 && x < 620) && (y > 300 && y < 350))
            {
                kill(pid, SIGKILL);
                show_bmp(0,0,"start.bmp");
                break;
            }
            
	    }
    }
	return ;
}
//创建管道文件
int create_fifo()
{
    //检测管道文件是否存在，不存在就创建
    int ret=access("/tmp/fifo",F_OK);
    if(ret == -1)
    {
        mkfifo("/tmp/fifo",0777); //创建管道文件

    }
    int fifo_fd=open("/tmp/fifo",O_RDWR);  //打开管道文件
    if(fifo_fd == -1)
    {
        perror("open fifo failed");
        return -1;
    }
    return fifo_fd;
}

//把slave命令写入管道文件
int slave_write_cmd(int fifo_fd,char *cmd)
{
    write(fifo_fd,cmd,strlen(cmd));
    return 0;
    
}

//视频播放功能
void show_video()
{
    DoubleCircleList*l create_VideoList();  //链表初始化
    
    Show_Bmp(0, 0, "3.bmp");  //显示视频主界面
    fifo_fd=create_fifo();
    int video_stop_cont_flags=1;
    
    int play_flag = 0;
    pid_t pid;
    pid = fork();  //创建子线程
    if(pid==0)
    {
    while(1)
    {
        execl("./mplayer", "./mplayer", "-slave", "-quiet", "input file=/tmp/fifo", "zoom", "-x", "700", "-y", "420", "geometry", "0:0", "p->data", NULL);
    }
    }
    
    while(1)
    {
        Get_Slide();
    
        //视频播放
        if(ts_x1>370 && ts_x1<425 && ts_y1>420 && ts_y1<480)
        {
            if(play_flag == 0) //当前是播放状态
            {
                kill(pid, SIGSTOP);  //子进程暂停
                play_flag = 1;
            }
            else
            {
                kill(pid, SIGCONT);  //子进程继续
                play_flag = 0; 
            }
            
        }
        
        //视频退出
        if(ts_x1>700 && ts_x1<800 && ts_y1>0 && ts_y1<60)
        {
            //杀死当前子进程
            kill(pid , SIGKILL);
            Show_Bmp(800, 480, 0, 0, "func.bmp");
            close(fifo_fd);
            break;
            
        }
        
        //播放上一个视频
        if(ts_x1>250 && ts_x1<300 && ts_y1>420 && ts_y1<480)
        {
            //杀死当前子进程
            kill(pid , SIGKILL);
            
            p=p->prev;
            if(p==list)
            {
                p=p->prev;
            }
            //创建新的子进程去播放上一首
            pid = fork();
            if(pid == 0)
            {
                execl("./mplayer", "./mplayer", "-slave", "-quiet", "input file=/tmp/fifo", "zoom", "-x", "700", "-y", "420", "geometry", "0:0", "p->data", NULL);  
            }
        }
        
        //播放下一个视频
        if(ts_x1>500&&ts_x1<550 && ts_y1>420&&ts_y1<480)
        {
            //杀死当前子进程
            kill(pid , SIGKILL);
            
            p=p->next;;
            if(p==list)
            {
                p=p->next;
            }
            //创建新的子进程去播放上一首
            pid = fork();
            if(pid == 0)
            {
                execl("./mplayer", "./mplayer", "-slave", "-quiet", "input file=/tmp/fifo", "zoom", "-x", "700", "-y", "420", "geometry", "0:0", "p->data", NULL);    
            }
        
        }
        
        //视频快进
        if(ts_x1>440&&ts_x1<490 && ts_y1>420&&ts_y1<480)
        {
        
            slave_write_cmd(fifo_fd,"seek +5\n");
        
        }
        
        //视频快退
        if(ts_x1>310&&ts_x1<360 && ts_y1>420&&ts_y1<480)
        {
        
            slave_write_cmd(fifo_fd,"seek -5\n");
        
        }
        
        //音量增加
        if(ts_x1>70&&ts_x1<110 && ts_y1>420&&ts_y1<480)
        {
            slave_write_cmd(fifo_fd,"volume +200\n");
        }
        
        //音量减少
        if(ts_x1>120&&ts_x1<160 && ts_y1>420&&ts_y1<480)
        {
            slave_write_cmd(fifo_fd,"volume -200\n");
        }
        
        //暂停/继续
        if(ts_x1>560&&ts_x1<610 && ts_y1>420&&ts_y1<480)
        {
        
            if(video_stop_cont_flags == 1)
            {
                slave_write_cmd(fifo_fd,"pause\n");
                video_stop_cont_flags=2;
            }
            else if(video_stop_cont_flags == 2)
            {
                slave_write_cmd(fifo_fd,"pause\n");
                video_stop_cont_flags=1;
                
            }
    
        }
    
        //视频静音
        if(ts_x1>690&&ts_x1<740 && ts_y1>420&&ts_y1<480)
        {
            slave_write_cmd(fifo_fd,"mute\n");
        }
    }
}


/* 
    播放视频
 */
void play_videos(char* name)
{
    DoubleCircleList*l create_VideoList();


    sprintf(buf,"mplayer -slave -quiet -geometry 0:0 -zoom -x 800 -y 480 %s &",name);
}

/*
    显示开始界面
*/

void lcd_start_ui()
{
    show_bmp(0,0,"start.bmp");
    int x,y;
    while(1)
    {
        get_user_touch(&x,&y);
        if(x>=90&&x<=250&&y>=280&&y<=390)
        {
            show_bmps();
        }
        if(x>=280&&x<=450&&y>=280&&y<=390)
        {
            show_bmp(0,0,"music.bmp");
            //play_music("1.mp3");
            /*多进程编程实现音乐播放器*/
            play_musics();
        }
        if(x>=510&&x<=660&&y>=280&&y<=390)
        {
            play_video("1.mp4");
        }
    }
    
}