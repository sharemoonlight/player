#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "bmp.h"
#include "lcd.h"

/*
    LCD_DrawBMP:显示图片
    @x:图片初始的横坐标
    @y:图片初始的纵坐标
    @*bmpname:图片文件的名字
*/

void LCD_DrawBMP(int x,int y,const char *bmpname)
{
	unsigned char buf[4];
	int fd=open(bmpname,O_RDWR);
	if(fd==-1)
    {
	    perror("open bmp failed");
	    return;
	}

	/*读魔数*/
	lseek(fd,0,SEEK_SET);
	read(fd,buf,2);
	if(buf[0]!=0x42||buf[1]!=0x4D)
    {
	     printf("this picture is not bmp!\n");
	     return;
	}	

	/*读位图宽度*/
	int bmp_w=0;
	lseek(fd,0x12,SEEK_SET);
	read(fd,&bmp_w,4);

	/*读位图高度*/
	int bmp_h=0;
	lseek(fd,0x16,SEEK_SET);
	read(fd,&bmp_h,4);

	/*读图片色深*/
	int bmp_colordepth=0;
	lseek(fd,0x1C,SEEK_SET);
	read(fd,&bmp_colordepth,2);
	printf("bmp:%1d*%1d*%1d\n",bmp_w,bmp_h,bmp_colordepth);

	/*读像素数组内容，并通过画点函数画出来*/
	lseek(fd,54,SEEK_SET);//把光标偏移到像素数组位置
	int i,j;
	for(i=0;i<bmp_h;i++)
    {
		for(j=0;j<bmp_w;j++)
        {
		  int color=0;
		  read(fd,&color,bmp_colordepth/8);
		  lcd_draw_point(x+j,y+(bmp_h>0?(bmp_h-1-i):i),color);//位图高度
		}
		lseek(fd,(4-bmp_colordepth/8*bmp_w%4)%4,SEEK_CUR);//跳过无用数据
	}
	close(fd);
}

/*
	show_bmp :显示bmp图片
	@x0 : 图片的初始横坐标
	@y0 : 图片的初始纵坐标
	@bmpfile : 要显示哪个图片
	返回值 :
        返回  0  表示解析bmp图片成功 
		返回 -1  表示打开bmp文件失败
        返回 -2  表示打开的文件不是bmp文件
        返回 -3  表示解析的图片不是32或24位图
*/


void show_bmp(int x0,int y0,char* bmpfile)
{
    //打开图片文件
    int fd = open (bmpfile,O_RDWR);
    if(fd==-1)
    {
	    perror("open bmp failed");
	    return;
	}
    //判断是不是bmp文件 读魔数
    unsigned char buf[4];
    lseek(fd,0,SEEK_SET);
    read(fd,buf,2);
    if(buf[0] != 0x42 || buf[1] != 0x4d)
    {
        printf("this picture is not bmp!\n");
	    return;
    }
    //获取图片的属性 宽，高，色深
    /*读位图宽度*/
	int bmp_w=0;
	lseek(fd,0x12,SEEK_SET);
	read(fd,&bmp_w,4);

	/*读位图高度*/
	int bmp_h=0;
	lseek(fd,0x16,SEEK_SET);
	read(fd,&bmp_h,4);

	/*读图片色深*/
	int bmp_colordepth=0;
	lseek(fd,0x1C,SEEK_SET);
	read(fd,&bmp_colordepth,2);
    printf("bmp:%1d*%1d*%1d\n",bmp_w,bmp_h,bmp_colordepth);
    //获取像素数组
    int line_vaild_bytes = bmp_w * bmp_colordepth/8;//一行的有效字节数
    int line_bytes ;//一行的总字节数 = 有效的字节数 + 填充字节
    int fill_bytes = 0;//填充字节

    if(line_vaild_bytes%4)
    {
        fill_bytes = 4 - line_vaild_bytes%4;
    }
    line_bytes = line_vaild_bytes + fill_bytes;//一行的总字节数
    int tolal_bytes = line_bytes * abs(bmp_h);//整个像素数组的大小
    //需要空间保存像素数组
    unsigned char color_buf[tolal_bytes];
    lseek(fd,0x36,SEEK_SET);
    read(fd,color_buf,tolal_bytes);
    //在屏幕上显示每个像素点
    unsigned char a,r,g,b;
    int color;
    int i = 0;
    for(int y = 0;y<abs(bmp_h);y++)
    {
        for(int x = 0;x < bmp_w;x++)
        {
            b = color_buf[i++];//b = color_buf[i]; i = i + 1
            g = color_buf[i++];
            r = color_buf[i++];

            if(bmp_colordepth == 32)//色深
            {
                a = color_buf[i++];
            }
            else//24色深
            {
                a = 0;
            }
            color =( (a << 24)|(r << 16) | (g << 8) | b); //合成当前第一个像素点的颜色值
            
            //在屏幕上对应位置显示
            lcd_draw_point(x + x0,  bmp_h > 0? bmp_h -1- y + y0 : y + y0,color);
        }
            //每一行的末尾,如果字节数不是4的倍数,需要填充几个字节
            i = i + fill_bytes;
    }
    //关闭bmp文件
    close(fd);
}


