#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<wait.h>
#define MAX 1024
#define NUM 16

int main()
{
  while(1)
  {

    int flag =0; //redirect flag 
   int j=0;
   int i=0;
   char *ret=NULL;
   char *myargv[NUM]={NULL};
   char buf[MAX]={0};
   printf("[lijinhu@localhost ~]# ");
   scanf("%[^\n]%*c",buf);
   myargv[i++]=strtok(buf," ");


   if(!strcmp(">",myargv[0]))
   {
     flag=3;
   }



   else 
   {
    while(ret=strtok(NULL," "))
     {
       //追加重定向
      if(!strcmp(">>",ret))//add redirect
      {
        flag=2;
         break;
     }
      //输出重定向
      if(!strcmp(">",ret))
      {
         flag=1;
         break;
      }
      //输入重定向
      if(!strcmp("<",ret))
      {
        flag=4;
        break;
      }
       myargv[i++]=ret;
    }
   }
   
    myargv[i]=NULL;

    int id=fork();
    if(id==0)
    {

      //追加重定向
      if(flag==2)
      {
        close(1);
        int fd = open(strtok(NULL," "),O_APPEND|O_CREAT|O_WRONLY,0664);
   if(fd<0)
   {
     perror("open error");
   }
      }
   //输出重定向
     if(flag==1)
     {
     close(1);    
   int fd = open(strtok(NULL," "),O_WRONLY|O_CREAT,0664);
   if(fd<0)
   {
     perror("open error");
   }
     }
    if(flag==4)
    {
      close(0);
      //把某个文件的内容作为标准输入
      
   int fd = open(strtok(NULL," "),O_RDONLY,0664);
   if(fd<0)
   {
     perror("open error");
   }
    }

  //清空
     if(flag==3)
     {
       int fd=open(strtok(NULL," "),O_TRUNC|O_CREAT,0664);//O_TRUNC delete file data
   if(fd<0)
   {
     perror("open error");
   }
       printf("open file\n");
     }
     else 
        execvp(myargv[0],myargv);
        exit(1);
    }
    else
    {
        waitpid(-1,NULL,0);
    }
 }
  return 0;
}
