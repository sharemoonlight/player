#ifndef _LCD_H__
#define _LCD_H__

void lcd_init();/*屏幕初始化*/
void lcd_uninit();/*解除映射和关闭文件*/
void clear_lcd(int color);//清屏
/*
    lcd_draw_point 画点函数，将（x，y）坐标上的像素点显示为color颜色
    @x      像素点的横坐标
    @y      像素点的纵坐标
    @color  像素点的颜色
*/
void lcd_draw_point(int x,int y,int color);
/* 
screen_square ：画长方形
参数：
    int x0 ：起始点的横坐标
    int y0 ：起始点的纵坐标
    int  w ：长方形的宽
    int  l ：长方形的长
    int color ：长方形的颜色
 */
void srceen_square(int x0,int y0,int w,int l,int color);

/* 
screen_round ：画圆
参数：
    int x0 ：圆心的X轴
    int y0 ：圆心的Y轴
    int r  ：圆的半径
    int colour ：圆的颜色
 */
void srceen_round(int x0,int y0,int r,int color);
/* 
taiji ：画一个太极
参数：
    x ：中心点的X坐标
    y ：中心点的Y坐标
    r ：大圆半径
    col1 ：一边的颜色
    col2 ：另一半的颜色
 */
void taichi(int x0,int y0,int r,int color1,int color2);
void taichi02(int x0,int y0,int r,int color1,int color2);
void taichi03(int x0,int y0,int r,int color1,int color2);
void taichi04(int x0,int y0,int r,int color1,int color2);

/* 
five_Pointed ：画五角星
参数：
    x ：五角星的在正中心点的X坐标
    y ：五角星的在正中心点的Y坐标
    R ：中心点到外顶点的长度
    color:五角星的颜色
    yDegree ：五角星的倾斜程度
 */
void five_Pointed(int x,int y,int R,int color,int yDegree);
void national_flag();
#endif