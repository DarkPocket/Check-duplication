#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED


#include<windows.h>
/*
链表是否有头节点
影响 遍历和计算长度

cpp还是c 影响快排代码
        cpp      return &tmpHead;
        c        return tmpHead.pNext;
*/

#define INT_Max  2147483647
struct NODE
{
        //by black

        int NumID;
     long   long int FileSizeB;

        double FileSizeGB;  //   = FileSizeB /(1024*1024*1024)= FileSizeB / 1073741824
        //  一 FileSizeB保存完整大小 超过后转成以GB为单位的FileSizeGB，
        //二 以MB 为划分 ,FileSizeB 保存小于1MB的 FileSizeGB保存 GB级别
        int FileSizeHigh;
        int FileSizeLow;
        //三 用两个变量保存  FileSizeHigh=FileSize/int
        // FileSizeLow=FileSize%int

        char FileName[MAX_PATH];
        char FilePath[MAX_PATH];
        char Extension[MAX_PATH / 10] ;//文件后缀名
        char FileMD5[40];

        //38b8c2c1093dd0fec383a9d9ac940515  32

        struct node *pNext;



} node, *pnode;

struct NODE *Create_plist();// 创建 链表
void traverse_list(struct NODE *pHead);

int is_empty(struct NODE *pHead);// 链表是否为空
int length_list(struct NODE *pHead);

int insert_list(struct NODE *pHead, int newstr, int x); // 在第i个链表前面插入 新节点   值为x
int add_list(struct NODE *pHead, struct NODE *qList);  //添加节点
int delete_list(struct NODE *pHead, int j, int *x); //删除j节点后面的节点


//void sort_list(struct NODE *pHead ) ;
void Bublle_sort_list(struct NODE *  );

int CopyListNode ( struct  NODE * Copy_pHead, struct  NODE * qHead );

void ListDestroy(struct NODE*head);


//链表快排算法
struct NODE* partitionList( struct NODE* lowPre,  struct NODE* low,  struct NODE* high);
void qsortList( struct NODE *headPre,  struct NODE*head,  struct NODE*tail);
struct NODE *quickSortList( struct NODE *head);

void showPiont(struct NODE *p );

#endif // LINKEDLIST_H_INCLUDED
