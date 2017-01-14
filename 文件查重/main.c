
#include "md5c.h"
#include "LinkedList.h"
#include <string.h>
#include <stdio.h>
#include<malloc.h>
#include<windows.h>

long int FileCount = 0;
double AllFileSizes = 0;


// 检查大小阈值 1024KB ,低于的跳过

#define CHECK_MIN_SIZE 1024000  // CheckMinSize 512000





// bug  单个文件超过2GB  文件大小出错

void FilePathFindExten( TCHAR cFileName[ MAX_PATH ] , TCHAR Exten[MAX_PATH / 10 ])
{
        //获得文件后缀名
        int len = 0, i, j, position = 0;

        len = strlen(cFileName);
        if (len < 1)
        {
                printf("\n 出错警告  文件名长度为0 \n");
                strcmp(Exten, "");
                return  ;
        }


        position = len;
        do
        {
                position--;
                if (position < 2)
                {
                        //无后缀名文件
                        strcmp(Exten, " ");
                        return  ;
                }
        }
        while (cFileName[position] != '.');
        j = 0;

        for (i = position + 1 ; i < len; i++)
        {
                Exten[j++] = cFileName[i];

        }

        if ((len - position) > (MAX_PATH / 10 - 1))
        {
                printf("\n 出错警告  文件名长度 可能过长\n");
                printf("%s \n", cFileName);
                Sleep(1000);
                return  ;
        }

        //   return Exten;
        return ;
}



void find(char * lpPath , struct NODE *pHead)

{

        char szFind[MAX_PATH], szFile[MAX_PATH] = {0};

        char FilePositTemp[MAX_PATH] = {0};

        WIN32_FIND_DATA FindFileData;

        HANDLE hFind;

        strcpy(szFind, lpPath);

        strcat(szFind, "\\*.*"); //这里一定要指明通配符，不然不会读取所有文件和目录

        hFind = FindFirstFile(szFind, &FindFileData);

        if (INVALID_HANDLE_VALUE == hFind)

        {
                printf("INVALID_HANDLE_VALUE error !!!  %d  \n  ", hFind);
                printf("文件地址 %s   \n  ", szFind);
                printf("\t\t  %ld \n", FileCount);
                return;
        }



        while (TRUE)

        {
                //dwFileAttributes是目标文件标记，&表示做与运算，FILE_ATTRIBUTE_DIRECTORY是文件夹的标志符
                // #define FILE_ATTRIBUTE_DIRECTORY            0x00000010
                if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                        //这是一个普通目录
                {
                        //不是当前路径或者父目录的快捷方式
                        if (FindFileData.cFileName[0] != '.')
                        {
                                //设置下一个将要扫描的文件夹路径
                                strcpy(szFile, lpPath);

                                strcat(szFile, "\\");

                                strcat(szFile, FindFileData.cFileName);



                                if (  strcmp( FindFileData.cFileName, "$RECYCLE.BIN") == 0) // $RECYCLE.BIN
                                {
                                        //跳过回收站
                                        printf("回收站\n" );

                                }
                                else
                                {
                                        //递归遍历该目录
                                        find(szFile, pHead);


                                }


                        }

                }

                else

                {

                        char Extension[MAX_PATH / 10] = {0};
                        //文件后缀名
                        FilePathFindExten(FindFileData.cFileName, Extension);

                        long  long int FileSize = 0;
                        FileSize =  (FindFileData.nFileSizeHigh * (MAXDWORD + 1)) + FindFileData.nFileSizeLow;


                        AllFileSizes += (double)FileSize / 1024 ;
                        char FilePosit[MAX_PATH] = {0};
                        strcpy(FilePosit, lpPath);
                        strcat(FilePosit, "\\");



                        //    printf("%s ", FilePosit); //文件位置
                        //  printf("%s ", FindFileData.cFileName ); //文件名
                        //  printf("%s ", Extension); //文件后缀名
                        //     printf(" %ld 字节（%ldKB） \n" , FileSize, FileSize / 1024); //文件大小

                        FileCount++;

                        struct NODE  *pNew = (struct NODE *)malloc(sizeof(struct NODE));
                        if (NULL == pNew)
                        {
                                printf("创建链表节点失败，终止 \n");
                                return -2;
                                //   exit(-1);
                        }
                        pNew->NumID = FileCount;
                        strcpy(  pNew->FilePath, FilePosit );
                        strcpy(pNew->FileName, FindFileData.cFileName );   //  pNew->FileName = qList->FileName;
                        pNew->FileSizeB =  FileSize;
                        pNew->FileSizeGB = (double)FileSize / 1073741824;

                        pNew->FileSizeHigh = FileSize / (INT_Max) ;
                        pNew->FileSizeLow = FileSize % (INT_Max) ;

                        strcpy(  pNew->FileMD5, ""  ); //  pNew->FileMD5 = 0;




                        add_list(pHead, pNew);



                }

                if (!FindNextFile(hFind, &FindFileData))
                        //如果是当前路径或者父目录的快捷方式，或者是普通目录，则寻找下一个目录或者文件
                {
                        break;
                }

        }

}


//compare check  repeat


int calculateFilePiontMD5 (  struct NODE *p )
{


        unsigned char digest[16] = {0};
        char FilePositTemp[MAX_PATH] = {0};

        if (NULL == p)
        {
                printf(" 节点 为NULL ,MD5计算 error !\n");
                return -3;
        }


        if (  p->FileSizeB <= CHECK_MIN_SIZE )
        {

                strcpy(p->FileMD5, "");
        }
        else
        {

                //大于1MB 计算MD5
                strcpy(FilePositTemp, p->FilePath);
                strcat( FilePositTemp, "//");
                strcat( FilePositTemp, p->FileName);
                MD5File(FilePositTemp, digest);

                MD5HexToChar (digest, p->FileMD5);

        }


        return 0;
}



int  FileListWrite(  char filepath[MAX_PATH], char TxtName[MAX_PATH], struct NODE *pHead )
{
        //将链表写入文件
        FILE *fp, *fpTemp;
        char fileName[MAX_PATH] = {0};

        char PathTemp [MAX_PATH] = {0};

        long int counts = 0;
        long  long int allSize = 0;

        int j = 0;


        strcpy(PathTemp , filepath);

        wsprintf(PathTemp, "%s\\%s.txt", filepath , TxtName  )  ;



        printf("打开 %s  \n  ", PathTemp);


        do
        {
                if (  (fpTemp = fopen(PathTemp, "r")) != NULL )
                {
                        printf(" %s 已存在\n  ", PathTemp);
                        fclose(fpTemp);
                        j++;
                        wsprintf(PathTemp, "%s\\%s%d.txt", filepath , TxtName, j   )  ;
                        //    wsprintf( PathTemp , "%s\\list%d.txt" , filepath  , j );
                }

        }
        while (  fpTemp != NULL  );


        strcpy(fileName, PathTemp  );



        //   sprintf(  fileName ,"\\list%d.txt",i );



        if ((fp = fopen(fileName, "w")) == NULL)
        {
                printf("写入到  %s \n  ", fileName);
                printf("%s  open error !\n", fileName);
                Sleep(5000);
                return -2;
        }

        char FilePositTemp[MAX_PATH] = {0};
        unsigned char digest[16] = {0};
        struct NODE *p = pHead->pNext;

        int i = 0;
        while ( NULL != p)
        {

                counts++;
                allSize = p->FileSizeB + allSize;
                //   fprintf(fp, "%3d. \n", p->NumID);
                fprintf(fp, "%s", p->FilePath);
                fprintf(fp, "\t%s\n", p->FileName);
                if (  p->FileSizeGB <= 0.000976)
                {
                        fprintf(fp, "%ld B(字节)  ", p->FileSizeB);
                }
                else
                {

                        /*     //大于1MB 计算MD5
                             strcpy(FilePositTemp, p->FilePath);
                             strcat( FilePositTemp, "//");
                             strcat( FilePositTemp, p->FileName);
                             MD5File(FilePositTemp, digest);
                             //    char MD5_Char[50] = {0};
                             MD5HexToChar (digest, p->FileMD5);
                        */

                        if ( p->FileSizeGB <= 1 )
                        {
                                fprintf(fp, "   %lf MB  ", p->FileSizeGB * 1024);
                        }
                        else
                        {
                                fprintf(fp, "   %lf GB  ", p->FileSizeGB);
                        }

                }

                fprintf(fp, "\n");


                if (strcmp(p->FileMD5, "") != 0)
                {
                        for (i = 0; i < 32; i++)
                        {
                                fprintf(fp, "%c", p->FileMD5[i]);
                        }
                        fprintf(fp, "\n");
                }
                else
                {
                        fprintf(fp, "\n");
                }




                p = p->pNext;


                fprintf(fp, "\n");
        }

        counts = counts / 2;
        allSize = allSize >> 1;

        fprintf(fp, "    \n" );
        fprintf(fp, " %ld 个 文件  \n" ,    counts);
        fprintf(fp, "共  %lld  MB  \n" ,    allSize / 1048576);



        if (fclose(fp))
        {
                printf("Can not close the%s!\n", fileName);
                return -1;
        }

        printf("排序写入已完成  \n");
        return 0;
}


int traverse_file_list_check_repeat ( char filepath[MAX_PATH], struct NODE *pHead  )
{
        //排序遍历链表查找重复文件


        struct NODE *pList = (  struct NODE *)malloc(sizeof(  struct NODE));  // NULL  ;


        pList  =  quickSortList(pHead->pNext);
        struct NODE *p =  pList ;


        struct NODE *pFile = NULL;
        pFile = Create_plist();


        long  long int FileSizeCache = 0 ;

        struct NODE *qTemp = NULL  ;
        long int counts = 0;
        long  long int allSize = 0;

        qTemp = p;
        while ( NULL != p)
        {
                if (FileSizeCache == p->FileSizeB)
                {


                        calculateFilePiontMD5(qTemp);
                        calculateFilePiontMD5(p);
                        if ((strcmp(p->FileMD5, qTemp->FileMD5) == 0) && (strcmp(p->FileMD5, "") != 0))
                        {

                                struct NODE  *pNew1 = (struct NODE *)malloc(sizeof(struct NODE));
                                if (NULL == pNew1)
                                {
                                        printf("创建链表节点失败，终止 \n");
                                        return -2;

                                }
                                *pNew1 = *qTemp;
                                add_list(pFile, pNew1);

                                struct NODE  *pNew2 = (struct NODE *)malloc(sizeof(struct NODE));
                                if (NULL == pNew2)
                                {
                                        printf("创建链表节点失败，终止 \n");
                                        return -2;

                                }
                                *pNew2 = *p;
                                add_list(pFile, pNew2);
        counts++;
                                allSize = p->FileSizeB + allSize;
                        }



                }
                else
                {
                        FileSizeCache = p->FileSizeB ;
                }



                qTemp = p;
                p = p->pNext;

        }


        FileListWrite( filepath , "repeatList", pFile);

        printf("    \n" );
        printf(" %ld 个重复文件  \n" ,    counts);
        printf("共  %lld  MB  \n" ,    allSize / 1048576);


        ListDestroy(pList);

        ListDestroy(pFile);

      return 0;
}

struct NODE * SortListWriteFile (  char filepath[MAX_PATH], struct NODE *pHead )
{
        //排序遍历链表  写入文件


        struct NODE *pList = (  struct NODE *)malloc(sizeof(  struct NODE));  // NULL  ;


        pList  =  quickSortList(pHead->pNext);

        FileListWrite (   filepath, "SortList" , pList);

        return  pList ;

}

int menu (  char filepath[MAX_PATH], struct NODE *pHead )
{
        int select = 0;


        printf("1. 遍历文件夹并把内容输入到txt中  \n");

        printf("2. 遍历文件夹 按大小排序输入到txt中  \n");

        printf("3. 检查重复文件并把结果输入到txt文件中 \n");


        scanf("%d", &select);


        struct NODE * q = pHead;




        switch ( select )
        {
        case 0 :

                break  ;
        case 1 :
                //遍历文件夹并把内容输入到txt中
                FileListWrite( filepath, "List", pHead);
                break  ;
        case 2 :
                // 遍历文件夹 按大小排序输入到txt中
                q = SortListWriteFile( filepath, pHead);
                ListDestroy(q);
                q = NULL;
                break  ;

        case 3 :
                //检查重复文件并把结果输入到txt文件中
                traverse_file_list_check_repeat (filepath, pHead) ;
                break ;

        default :
                break ;
        }

        if (q)
        {
                ListDestroy(pHead);
                printf(" ListDestroy  traver  (pHead)   \n" );

        }
        else
        {

        }



        return 0;
}


void fun ( )
{

        struct NODE *pHead = NULL;
        pHead = Create_plist();


        struct NODE  *pNew = (struct NODE *)malloc(sizeof(struct NODE));
        if (NULL == pNew)
        {
                printf("创建链表节点失败，终止 \n");
                return -2;
                //   exit(-1);
        }


        char filepath[MAX_PATH] = "g:\\迅雷\\Profiles\\Torrents\\" ;

        printf("输入目标地址 （例如 F:\\\\qq  ）\n");
        // scanf("%s",filepath);

        printf("读取文件中，请稍等 \n");

        find(filepath, pHead);

        system("cls");

        if (is_empty(pHead))
        {
                printf("  文件信息链表为空 \n");
                return -5;
        }
        else
        {
                //   printf("  链表不空 \n");
        }



        length_list (pHead);




        menu(filepath, pHead);



        printf("扫描文件总大小为 " );
        if ( AllFileSizes > 0 && AllFileSizes < 1024 * 1024)
        {
                printf("   %lf MB  \n", AllFileSizes / 1024);
        }
        else
        {
                printf("   %lf GB  \n", AllFileSizes / 1048576);
        }

        printf("FileCount %ld \n", FileCount);




}

int  fun3(  char filepath[MAX_PATH]  )
{

        FILE *fp;
        char fileName[MAX_PATH] = {0};

        long int counts = 0;
        long  long int allSize = 0;



        strcpy(fileName, filepath);
        strcat(fileName, "\\list2.txt");



        if ((fp = fopen(fileName, "w")) == NULL)
        {
                printf("%s  open error !\n", fileName);
                Sleep(5000);
                return -2;
        }
        printf("输入txt地址为 %s \n", fileName);


}

void fun2( )
{

        char filepath[MAX_PATH] = "F:" ;


        printf("输入目标地址 %s \n", filepath);
        fun3(filepath );

}

int main (void)
{
        /*
        int i=0;
        i= 2147483647;
        long j=0;
        j=i*2;
        printf("%d  ",i);
        long long int l=9223372036854775807;
        printf("%ld  ",j);
        */



        fun ( );


        //long long int 9223372036854775807

        printf("over \n");

        system("pause");
        return  0;
}
