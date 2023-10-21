#ifndef _FUN_H__
#define _FUN_H__


/*
    show_bmps：电子相册
    根据手指的上下左右滑动播放图片
*/
void show_bmps();

/*
    播放音乐
*/
void* play_music(void* arg);

/* 
    播放视频
 */
void play_video(char* name);

/*
    显示开始界面
*/
void lcd_start_ui();
/*多进程编程实现音乐播放器*/
void play_musics();

#endif