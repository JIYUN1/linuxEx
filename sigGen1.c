#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<signal.h>
#include<unistd.h>


void sigHandler(int sig)
{

    static int counter = 0;
    printf("sig : %d\n counter: %d\n", sig, counter);
    counter++;
}


int main(int argc, char *argv[])
{
   pid_t pid;
   int fd,i, byteCount;
   char buffer[10];
   memset(buffer, 0, 10); // 0, 10 set : after atoi 

   //signal handler register
   signal(SIGINT, sigHandler);

   pid = getpid();
   sprintf(buffer, "%d", pid); // write %d test.txt after read pid value 

   fd = open("./test.txt", O_RDWR | O_CREAT | O_TRUNC, \
             S_IRWXU | S_IWGRP | S_IRGRP | S_IROTH);

          
   byteCount = write(fd, buffer, strlen(buffer));
   close(fd);
 

   pid = atoi(argv[1]); // pid value transfer
   printf("send signal proc :%d\n", pid);

   for(i=0; i<5; i++)
   {
     kill(pid, SIGINT); // -> sigGen2 
     pause();
   }

   return 0;

}
