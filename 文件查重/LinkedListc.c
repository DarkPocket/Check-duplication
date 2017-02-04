#include "LinkedList.h"
#include <string.h>
#include <stdio.h>
#include<malloc.h>






// 创建 链表
struct NODE *Create_plist()
{
        int len;
        int i = 0;
        int val = 0; //临时存放数据
        // 头节点
        struct NODE *pHead = (struct NODE *)malloc(sizeof(struct NODE));
        if (pHead == NULL)
        {
                printf("创建链表失败，终止 \n");
                exit(-1);
        }
        // 尾节点
        pHead->pNext=NULL;
pHead->FileSizeB=-1;
pHead->FileSizeGB=-1;
  /*      struct NODE *pTail = pHead;
        pTail->pNext = NULL;
*/
        return pHead;

}



void traverse_list(struct NODE *pHead)
{
        struct NODE *p = pHead ;//->pNext;

        if ( p == NULL )
        {
                printf("链表 NULL \n");
                return ;
        }

        int i = 0, j = 0;
        while ( NULL != p)
        {
                printf("%3d. ", p->NumID);
                //     printf("  %s ", p->FilePath);
                printf("  %s ", p->FileName);
                if (  p->FileSizeGB <= 0.000976)
                {
                        printf("   %ld B (字节)  ", p->FileSizeB);
                }
                else
                {
                        if ( p->FileSizeGB <= 1 )
                        {
                                printf("   %0.4lf MB  ", p->FileSizeGB * 1024);
                        }
                        else
                        {
                                printf("   %0.4lf GB  ", p->FileSizeGB);
                        }

                }
                printf("\n");
                if (strcmp(p->FileMD5, "") != 0)
                {
                        for (i = 0; i < 32; i++)
                        {
                                printf("%c", p->FileMD5[i]);
                        }
                }
                else
                {
                        printf(" ");
                }

                printf("\n");


                p = p->pNext;

                j++;
                //     printf("  \n");
        }
        printf("总共有 %d个 \n", j);
        return ;

}

void showPiont(struct NODE *p )
{
        int i, j;

    printf("%3d. ", p->NumID);
        printf("  %s ", p->FilePath);
        printf("  %s ", p->FileName);
        if (  p->FileSizeGB <= 0.000976)
        {
                printf("   %ld B (字节)  ", p->FileSizeB);
        }
        else
        {
                if ( p->FileSizeGB <= 1 )
                {
                        printf("   %0.4lf MB  ", p->FileSizeGB * 1024);
                }
                else
                {
                        printf("   %0.4lf GB  ", p->FileSizeGB);
                }

        }
        printf("\n");
        if (strcmp(p->FileMD5, "") != 0)
        {
                for (i = 0; i < 32; i++)
                {
                        printf("%c", p->FileMD5[i]);
                }
        }
        else
        {
                printf(" ");
        }

        printf("\n");
}

// 链表是否为空
int is_empty(struct NODE *pHead)
{
        if ( pHead->pNext == NULL )
        {
                return 1;
        }
        else
        {
                return 0;
        }

}

int length_list(struct NODE *pHead)
{
        long  int len = 0;
        struct NODE *p = pHead->pNext;

        while ( NULL != p)
        {
                len++;
                p = p->pNext;

                if (len < 0)
                {
                        printf(" 链表len异常为%ld ，长度可能过长 会触发异常 \n", len);
                        return -2;
                }

        }
        printf(" 链表len=%ld \n", len);
        return len;

}
int add_list(struct NODE *pHead, struct NODE *qList)  //添加节点
{

        int i = 0;
        struct NODE *p = pHead;

        while ( NULL != p->pNext)
        {

                p = p->pNext;
        }

        struct NODE *pNew = (struct NODE *)malloc(sizeof(struct NODE));
        if (pNew == NULL)
        {
                printf("创建链表节点失败，终止 \n");
                exit(-1);
        }

        /*
                pNew->NumID = qList->NumID;
                strcpy(  pNew->FilePath, qList->FilePath );   //  pNew->FilePath = qList->FilePath;
                strcpy(pNew->FileName, qList->FileName );     //  pNew->FileName = qList->FileName;
                pNew->FileSizeB = qList->FileSizeB;
                pNew->FileSizeGB = qList->FileSizeGB;
                strcpy(  pNew->FileMD5, qList->FileMD5  );  //  pNew->FileMD5 = qList->FileMD5;
        */

        *pNew = *qList;

        p->pNext = pNew;

        pNew->pNext = NULL;


        /*
                pNew->data = val;
                pTail->pNext = pNew;
                pNew->pNext = NULL;
                pTail = pNew; //尾节点
        */
        return 0;
}



// 在第i个链表前面插入 新节点   值为x
int insert_list(struct NODE *pHead, int newstr, int x)
{
        int i = 0;
        struct NODE *p = pHead;
        struct NODE *q;
        while (NULL != p && i < newstr - 1)
        {
                p = p->pNext;
                i++;

        }
        if (i > newstr - 1 || NULL == p)
        {
                return -1;
        }


        struct NODE  *pNew = (struct NODE *)malloc(sizeof(struct NODE));
        if (NULL == pNew)
        {
                printf("创建链表节点失败，终止 \n");
                return -2;
                //   exit(-1);
        }
        pNew->NumID = x;

        q = p->pNext;
        p->pNext = pNew;
        pNew->pNext = q;

        return 1;

}


//删除j节点后面的节点
int delete_list(struct NODE *pHead, int j, int *x)
{
        int i = 0;
        struct NODE *p = pHead, *s;
        struct NODE *q;
        while (NULL != p->pNext && i < j - 1)
        {
                p = p->pNext;
                i++;

        }
        if (i > j - 1 || NULL == p->pNext)
        {
                return -1;
        }


        //  struct NODE  *pNew = (struct NODE *)malloc(sizeof(struct NODE));

        //  pNew->data = x;

        q = p->pNext;
        *x = q->NumID; //data

        //删除p节点后面的节点
        // p->pNext=p->pNext->pNext;
        s = p->pNext;
        p->pNext = s->pNext;
        free(q);
        q = NULL;


        // pNew->pNext= q;

        return 1;

}

void Bublle_sort_list(struct NODE *pHead )
{
        //冒泡排序节点中的数据
        int i, j, t;
        struct NODE *p, *q;
        int len;
        len = length_list(pHead);
        i = j = t = 0;


        for (i = 0, p = pHead->pNext; i < len - 1; i++, p = p->pNext)
        {
                for (j = i + 1, q = p->pNext; j < len; j++, q = q->pNext)
                {
                        if (p->NumID > q->NumID)  //if (p->data > q->data)
                        {
                                t = p->NumID;
                                p->NumID = q->NumID;
                                q->NumID = t;
                        }


                }
        }

        return ;

}

struct NODE * CopyListNodes (  struct  NODE * qSource, struct  NODE * pCopy )
{
        //把qSource复制一份到pCopy中
        pCopy = (struct NODE *)malloc(sizeof(struct NODE));

         printf("copy 链表  \n");

        if ( pCopy == NULL)
        {
                printf("创建链表失败，终止 \n");
                exit(-1);
        }

        *pCopy = *qSource;
        struct NODE   *pTail = pCopy;

        qSource = qSource->pNext;
        while (qSource != NULL)
        {

                struct  NODE *pNew = (struct  NODE *)malloc(sizeof(struct  NODE)) ;
                if ( pNew  == NULL)
                {
                        printf("创建链表失败，终止 \n");
                        exit(-1);
                }

                *pNew = *qSource;
                //printf("qSource  %d  \n",qSource->num);
                //  printf(" pTail  %d  data  %d  \n", pTail->num, pTail->data);
                //   printf(" pNew %d  data  %d  \n", pNew->num, pNew->data);

                pNew->pNext = NULL;

                pTail->pNext = pNew;
                pTail = pNew;

                qSource = qSource->pNext;


        }

        pTail->pNext = NULL;


     printf("copy 链表 完成  \n");

        return pCopy;

}

int CopyListNode ( struct  NODE * Copy_pHead, struct  NODE * qHead )
{
        //by black


        *qHead = *Copy_pHead;



        Copy_pHead = Copy_pHead->pNext;

        struct NODE   *pTail = qHead;

        printf("复制链表中\n" );

        while ( NULL != Copy_pHead)
        {

                struct  NODE *pNew = (struct  NODE *)malloc(sizeof(struct  NODE));

                *pNew = *Copy_pHead;


                pNew->pNext = NULL;

                //     printf("复制 val  %4d  data %2d \n", pNew->val , pNew->data);
                //    getchar();
                pTail->pNext = pNew;
                pTail = pNew;
                Copy_pHead = Copy_pHead->pNext;


        }

        return 0;
}

void ListDestroy(struct NODE*head)
{
        struct NODE *p, *q;
        // Destroy
        p = head;
        if (  NULL == head->pNext)
        {
        	 free(head);
        head = NULL;
                printf("  链表 NULL \n" );
                return  ;
        }



        while (p->pNext != NULL)
        {
                q = p->pNext;
                p->pNext = q->pNext;
                free(q);
        }
        free(p);
        free(head);
        head = NULL;
        p = NULL;

        return ;
}




struct NODE* partitionList( struct NODE* lowPre,  struct NODE* low,  struct NODE* high)
{
        //链表范围是[low, high)
            long   long int  key = low->FileSizeB; //排序标准
        struct NODE node1, node2;//比key小的链的头结点，比key大的链的头结点
        struct NODE* little = &node1, *big = &node2;
        struct NODE*i;
        for (  i = low->pNext; i != high; i = i->pNext)
                if (i->FileSizeB < key)
                {
                        little->pNext = i;
                        little = i;
                }
                else
                {
                        big->pNext = i;
                        big = i;
                }
        big->pNext = high;//保证子链表[low,high)和后面的部分连接
        little->pNext = low;
        low->pNext = node2.pNext;
        lowPre->pNext = node1.pNext;//为了保证子链表[low,high)和前面的部分连接
        return low;
}

void qsortList( struct NODE *headPre,  struct NODE*head,  struct NODE*tail)
{
        //链表范围是[low, high)
        if (head != tail && head->pNext != tail)
        {
                struct NODE* mid = partitionList(headPre, head, tail);//注意这里head可能不再指向链表头了
                qsortList(headPre, headPre->pNext, mid);
                qsortList(mid, mid->pNext, tail);
        }
}

struct NODE *quickSortList( struct NODE *head)
{
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        //链表快速排序
        if (head == NULL || head->pNext == NULL)
        {
                return head;
        }
        struct NODE tmpHead;
        tmpHead.pNext = head;
        qsortList(&tmpHead, head, NULL);
        //    return &tmpHead;
        return tmpHead.pNext;
}


struct NODE * SortList (   struct NODE *pHead )
{
	printf ( "SortList 链表  \n" );
	//排序遍历链表
	struct NODE *pList = NULL;
	//pList = CopyListNodes ( pHead, pList );


	pList =  quickSortList ( pHead->pNext );


	printf ( "SortList 链表 完成 \n" );
	return  pList ;


}


