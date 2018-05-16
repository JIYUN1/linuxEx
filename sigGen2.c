#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>

void sigHandler(int sig)
{

    static int counter = 0;
    printf("sig ;%d, counter : %d\n:", sig, counter);
    counter++;
}

int main(int argc, char*argv[])
{
    pid_t pid;
    int fd, i, byteCount;
    char buffer[10];

    //sig register
    signal(SIGINT, sigHandler);
    pause();

    fd = open("./test.txt", O_RDWR);
    byteCount = read(fd, buffer, 10);//read a pid value 
    if(byteCount == 0)
        printf("Can't read test.txt file. \n");

    pid = atoi(buffer);
    printf("pid : %d\n", pid);
    close(fd);

    kill(pid, SIGINT);
    pause();

    for(i=0; i<4; i++)
    {
        kill(pid, SIGINT);
        pause();
    
    }

    return 0;
}
