#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>


struct NODE
{
        int num;
        int data;
        char ch[100];


        struct node *pNext;



} node, *pnode;

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
        struct NODE *pTail = pHead;
        pTail->pNext = NULL;



        printf("输入需要生成的链表节点个数 \n");
        scanf("%d", &len);

        for (i = 0; i < len; i++)
        {
                printf("输入第%d个节点值 \n", i);
                scanf("%d", &val);

                struct NODE *pNew = (struct NODE *)malloc(sizeof(struct NODE));
                if (pNew == NULL)
                {
                        printf("创建链表节点失败，终止 \n");
                        exit(-1);
                }

                pNew->data = val;
                pTail->pNext = pNew;
                pNew->pNext = NULL;
                pTail = pNew; //尾节点



        }
        return pHead;

}

void traverse_list(struct NODE *pHead)
{
        struct NODE *p = pHead->pNext;

        while ( NULL != p)
        {
                printf(" %2d ", p->data);
                p = p->pNext;



        }
        printf("  \n");
        return ;

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
        int len = 0;
        struct NODE *p = pHead->pNext;

        while ( NULL != p)
        {
                len++;
                p = p->pNext;
        }
        printf(" 链表len=%d \n", len);
        return len;

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
        pNew->data = x;

        q = p->pNext;
        p->pNext = pNew;
        pNew->pNext= q;

        return 1;

}


//删除j节点后面的节点
int delete_list(struct NODE *pHead, int j, int *x)
{
 int i = 0;
        struct NODE *p = pHead,*s;
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
        *x=q->data;

//删除p节点后面的节点
       // p->pNext=p->pNext->pNext;
       s=p->pNext;
        p->pNext=s->pNext;
        free(q);
        q=NULL;


       // pNew->pNext= q;

        return 1;

}

void sort_list(struct NODE *pHead )
{
        int i, j, t;
        struct NODE *p, *q;
        int len;
        len = length_list(pHead);
        i = j = t = 0;


        for (i = 0, p = pHead->pNext; i < len - 1; i++, p = p->pNext)
        {
                for (j = i + 1, q = p->pNext; j < len; j++, q = q->pNext)
                {
                        if (p->data > q->data)
                        {
                                t = p->data;
                                p->data = q->data;
                                q->data = t;
                        }


                }
        }

        return ;

}




int main (void)
{
        struct NODE *pHead = NULL;
        int newstr;
        int x;
        pHead = Create_plist();

        printf("   traverse_list(pHead); \n");
          sort_list(pHead);
        traverse_list(pHead);
        /*
                if (is_empty(pHead))
                                printf("  链表为空 \n");
                else
                {
                        printf("  链表不空 \n");
                        }
        */

        printf("在第i个节点前面插入x值\n");
     //   scanf("%d %d",&newstr,&x);
     //   insert_list(pHead, newstr,  x);
   if ( delete_list(pHead, 3,&x))
{
        printf("删除成功，删除的为%d\n",x);

}
else
{
        printf("删除失败 \n");

}
        length_list(pHead);
        sort_list(pHead);
        traverse_list(pHead);
        printf("over \n");
        return  0;
}
