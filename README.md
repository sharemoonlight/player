项目名称 ：基于 Linux GEC6818 开发板 多媒体播放器

项目制作人 ：彭万翔

项目介绍 ：
	项目实现功能:实现电子相册，音乐播放器，视频播放器三种多媒体功能

主要用到工具:Visual Studio Code ,VMware Workstation 16 Player,SecureCRT,GEC6818 开发板,网线

	     Visual Studio Code ：主要实现代码的编写
	     VMware Workstation 16 Playe ：主要实现代码编译	           
	     Code写好的代码存入共享文件夹share内，Ubuntu找到这个共享文件夹路径进行 make 编译 ，编译好的 arm-linux 可执行文件存入
	     /home/china/tftpboot文件中。
	
	     网线 ：Ubuntu 和 SecureCRT 形成局域网进行文件传输
	
	     SecureCRT ：主要实现将可执行文件传入GEC6818 开发板
	                 根据 tftp -g -r 文件名 Ubuntu网址指令，将 Ubuntu 内 tftpboot 里面的文件 经过网线传输到 SecureCRT ，然后执行可执行文件下载到
	     GEC6818 开发板
	
	     GEC6818 开发板：显示效果

主要功能用到的函数：
	lcd.c:
	void lcd_init()//用映射屏幕初始化     void lcd_uninit() //解除映射和关闭文件 
	void get_usr_touch(int *x0,int* y0)//获取用户触摸屏的坐标 触屏事件 
	bmp.c:	
	void show_bmp(int x0,int y0,char* bmpfile)//显示bmp图片

​	touch.c:

​	void get_user_touch(int *x,int* y)//获取用户触摸屏的坐标

​	get_fingle_move()//获取手指滑动的方向

​	filelist.c:

​	DoubleCircleList* create_PictureList(void)//创建一个带头结点的循环双向图片链表

​	DoubleCircleList* create_MusicList(void)//创建一个带头结点的循环双向音乐链表

​	DoubleCircleList* create_VideoList(void)//创建一个带头结点的循环双向视频链表

​	这里我用了三个双向循环链表分部存储图片，视频和音乐

​	fun.c:

​	void show_bmps()//电子相册 根据手指的上下左右滑动播放图片

​	void play_musics()//多进程编程实现音乐播放器

​	show_video()//多线程编程实现视频播放器

​	void lcd_start_ui()//显示开始界面

项目开始图片：

​           ![start](C:\Users\18200\Desktop\粤嵌-\二阶段\并发\0-项目\Picture\pic\start.bmp)     
​		
​		