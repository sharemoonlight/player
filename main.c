#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "lcd.h"
#include "bmp.h"
#include "touch.h"
#include "filelist.h"
#include "fun.h"


// void* play_misic(void* arg)
// {
//     char buf[256] = {0};
//     sprintf(buf,"madplay ./1.mp3",(char*)arg);

//     system(buf);
// }

int main()
{ 
    /*初始化*/
    lcd_init();
    // pthread_t tid = -1;
    // int ret = pthread_create(&tid,NULL,play_misic,"./1.mp3");//创建一个线程播放音乐
    // if(ret != 0)
    // {
    //     printf("Create thread fail\n");
    //     return -1;
    // }
    // pthread_detach(tid);
    
    //clear_lcd(0xffffff);

    //搜索所有的MP3，MP4文件，链表
    // while(1)
    // {
    //     pid_t pid;
    //     pid = fork();
    //     if(pid == 0)
    //     {
    //         int r = execl("/bin/mplayer","dream.avi",NULL);
    //         if(r == -1)
    //         {
    //             //让子进程去执行另外一个程序
    //             perror("excel error");
    //             return -1;
    //         }
    //     }
    //     if(pid > 0)
    //     {
    //         wait (NULL);
        
    //     }
    // }


    //显示开始按钮
    // lcd_start_button();
    //get_fingle_move();


    // int rs = 0;
    // int i = 0;
    // //单独显示一张图片
    // // show_bmp(0,0,"1.bmp");
    
    //触摸
    // int i = 0;
    // int rs = 0;
    // while (1)
    // {
        
    //      rs = get_fingle_move();
        
    //     if (1 == rs || 3 == rs)
    //     {
    //         if (5 == i)
    //         {
    //             i = 0;
    //         }
    //         else
    //             ++i;
    //         show_bmp(0,0,bmps[i]);
    //     }
    //     else if (2 == rs || 4 == rs)
    //     {
    //         if (0 == i)
    //         {
    //             i = 5;
    //         }
    //         else
    //             --i;
    //         show_bmp(0,0,bmps[i]);
    //     }
    // }

    // clear_lcd(0x00ffff);
    // srceen_square(200,90,300,400,0xf00f00);

    lcd_start_ui();
    /*解除*/
    lcd_uninit();
    return 0;
}