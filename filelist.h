#ifndef _FILELIST_H__
#define _FILELIST_H__

//数据结点
typedef struct binode
{
    char * filename;
    struct binode* next;//指向下一个
    struct binode* prev;//指向前一个
}BiNode;

//头结点
typedef struct DoubleCirclelist
{
    BiNode* first;//first指针的前一个就是last

}DoubleCircleList;

/*
	add_node:增加数据结点
		@l:要添加到的链表
		@p:需要添加的数据结点
*/
void add_binode(DoubleCircleList*  l,BiNode* p);
/*
    creat_Picturelist:创建一个带头结点的循环双向图片链表
*/
DoubleCircleList* create_PictureList(void);

/*
    creat_Musiclist:创建一个带头结点的循环双向音乐链表
*/
DoubleCircleList* create_MusicList(void);

/*
    creat_Musiclist:创建一个带头结点的循环双向音乐链表
*/
DoubleCircleList* create_VideoList(void);


#endif

