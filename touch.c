#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/input.h>
#include "touch.h"
#include "lcd.h"
#include "bmp.h"
#include "filelist.h"



/*
//注意 : 触屏屏的分辨率是1024*600,lcd屏是800*480,等比例缩放
get_usr_touch :获取用户触摸屏的坐标
@x : 指向的空间保存的是x轴坐标
@y : 指向的空间保存的是y轴坐标
返回值 :
无
*/

void get_user_touch(int *x,int* y)
{
	struct input_event et;
	int fd=open("/dev/input/event0",O_RDONLY);
	if(fd==-1)
	{
	   perror("open event0 failed");
	   return ;
	}
	while(1)
	{
		int r = read(fd,&et,sizeof(et));
		if(r != sizeof(struct input_event))
		{
			continue;
		}
		if(et.type == EV_ABS && et.code==ABS_X)
		{
			*x = et.value*(1.0*800/1024);
		}
		if(et.type==EV_ABS && et.code==ABS_Y)
		{
			*y = et.value*(1.0*480/600);
		}
		if(et.type == EV_KEY && et.code == 330 && et.value == 0)
		{
			break;
		}
	}
	close(fd);
	
}



/*
	get_fingle_move；获取手指滑动的方向
	返回值：
	返回 UP  	1
	返回 DOWN 	2
	返回 LEFT	3
	返回 RIGHT 	4
	返回 -1 	失败
*/

int get_fingle_move()
{
	//1.获取坐标
	int x0 = -1,y0 = -1;//初始坐标
	int x1,y1;//实时坐标
	struct input_event et;
	int fd=open("/dev/input/event0",O_RDONLY);
	if(fd==-1)
	{
	   perror("open event0 failed");
	   return -1;
	}
	while(1)
	{
		int r = read(fd,&et,sizeof(et));
		if(r != sizeof(struct input_event))
		{
			continue;
		}
		if(et.type == EV_ABS && et.code==ABS_X)
		{
			if(x0 == -1)
			{
				x0 = et.value*(1.0*800/1024);
			}
			x1 = et.value*(1.0*800/1024);
		}
		if(et.type==EV_ABS && et.code==ABS_Y)
		{
			if(y0 == -1)
			{
				y0 = et.value*(1.0*480/600);
			}
			y1 = et.value*(1.0*480/600);
		}
		if(et.type == EV_KEY && et.code == BTN_TOUCH && et.value == 0)
		{
			break;
		}
	}
	close(fd);
	//判断上下左右
	int way;
	if(abs((y1-y0)/(x1-x0)) > 1)//向上或者向下
	{
		if(y1 > y0)
		{
			printf("DOWN!\n");
			way = 2;
		}
		else if(y0 > y1)
		{
			printf("UP!\n");
			way = 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if(x1 < x0)
		{
			printf("LEFT!\n");
			way = 3;
		}
		else if(x0 < x1)
		{
			printf("RIGHT!\n");
			way = 4;
		}
		else
		{
			return 0;
		}
	}
	
	return way;
}





 