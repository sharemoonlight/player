#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <math.h>
#include "lcd.h"

int* plcd = NULL;//指向帧缓冲的首地址

/*屏幕初始化*/
void lcd_init()
{
    int lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd == -1) 
    {
        perror("open /dev/fb0 error");
        return ;
    }
    plcd = mmap(NULL,//映射的地址
                    800 * 480 * 4, //映射区域的权限
                    PROT_READ | PROT_WRITE,//映射的权限
                    MAP_SHARED,//映射的方式
                    lcd_fd, //映射的文件
                    0);//映射的偏移量
    if (MAP_FAILED == plcd) 
    {
        perror("map /dev/fb0 error\n");
        return ;
    }
}
//解除映射和关闭文件
void lcd_uninit() 
{
    int lcd_fd = open("/dev/fb0", O_RDWR);
    munmap(plcd, 800 * 480 * 4);
    close(lcd_fd);
}

/*
    lcd_draw_point 画点函数，将（x，y）坐标上的像素点显示为color颜色
    @x      像素点的横坐标
    @y      像素点的纵坐标
    @color  像素点的颜色
*/
void lcd_draw_point(int x,int y,int color)
{
    
    if(x >= 0 && x < 800 && y >= 0 && y <= 480)
    {
        *(plcd + 800 * y + x) = color;
    }
}
//清屏
void clear_lcd(int color)
{
    for ( int y = 0; y < 480; y++)
    {
        for ( int x = 0; x < 800; x++)
        {
            lcd_draw_point(x,y,color); 
        }
    }
}
/* 
screen_square ：画长方形
参数：
    int x0 ：起始点的横坐标
    int y0 ：起始点的纵坐标
    int  w ：长方形的宽
    int  l ：长方形的长
    int color ：长方形的颜色
 */
void srceen_square(int x0,int y0,int w,int l,int color)
{
    for(int y = y0;y < w;y++)
    {
        for(int x = x0;x < l;x++)
        {
            lcd_draw_point(x,y,color);
        }
    }
}


/* 
screen_round ：画圆
参数：
    int x0 ：圆心的X轴
    int y0 ：圆心的Y轴
    int r  ：圆的半径
    int color ：圆的颜色
 */
void srceen_round(int x0,int y0,int r,int color)
{
    for ( int y = 0; y < 480; y++)
    {
        for ( int x = 0; x < 800; x++)
        {
            if((x - x0)*(x - x0) +(y - y0)*(y - y0) <= r*r)
            {
                lcd_draw_point(x,y,color); 
            } 
        }
    }
}




