#ifndef _TOUCH_H__
#define _TOUCH_H__
#define UP 		1
#define DOWN 	2
#define LEFT  	3
#define RIGHT	4

void get_user_touch(int *x,int* y);
int get_coordinate(int *x,int *y);
int get_fingle_move();

#endif