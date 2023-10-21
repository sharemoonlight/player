#include <stdio.h>
#include <stdlib.h>
#include "filelist.h"

/*
	add_node:增加数据结点
		@l:要添加到的链表
		@p:需要添加的数据结点
*/
void add_binode(DoubleCircleList*  l,BiNode* p)
{
    if(l->first == NULL)
    {
        p->next = p;
        p->prev = p;
        l->first = p;
    }
    else
    {
        p->next = l->first;
        p->prev = l->first->prev;
        p->prev->next = p;
        l->first->prev = p;
    }
}

/*
    creat_Picturelist:创建一个带头结点的循环双向图片链表
*/
DoubleCircleList* create_PictureList(void)
{
   DoubleCircleList*  l = malloc(sizeof(l));
    l->first = NULL;
    int i = 1;
    while(1)
    {
        BiNode* p = malloc(sizeof(*p));
        p->filename = malloc(sizeof(p->filename));
        sprintf(p->filename,"q%d.bmp",i);
        p->next = NULL;
        p->prev = NULL;
        add_binode(l,p);
        i++;
        if(i == 9)
        {
            break;
        }
    }
    return l;
}

/*
    creat_Musiclist:创建一个带头结点的循环双向音乐链表
*/
DoubleCircleList* create_MusicList(void)
{
   DoubleCircleList*  l = malloc(sizeof(l));
    l->first = NULL;
    int i = 1;
    while(1)
    {
        BiNode* p = malloc(sizeof(*p));
        p->filename = malloc(sizeof(p->filename));
        sprintf(p->filename,"%d.mp3",i);
        p->next = NULL;
        p->prev = NULL;
        add_binode(l,p);
        i++;
        if(i == 4)
        {
            break;
        }
    }
    return l;
}


/*
    creat_Videolist:创建一个带头结点的循环双向视频链表
*/
DoubleCircleList* create_VideoList(void)
{
   DoubleCircleList*  l = malloc(sizeof(l));
    l->first = NULL;
    int i = 1;
    while(1)
    {
        BiNode* p = malloc(sizeof(*p));
        p->filename = malloc(sizeof(p->filename));
        sprintf(p->filename,"%d.mp4",i);
        p->next = NULL;
        p->prev = NULL;
        add_binode(l,p);
        i++;
        if(i == 4)
        {
            break;
        }
    }
    return l;
}