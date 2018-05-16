#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    int s, sig;
    if(argc != 3 || strcmp(argv[1], "--help")==0)
    printf("%s pid sig-num\n", argv[0]);
    sig = atoi(argv[2]);
    printf("argv[1]=%d\n", sig);
    s = kill(atoi(argv[1]), sig);

    if(sig !=0)
    {
        if(s == 1)
            printf("Error: system call kill()\n");
    }else
    {
        if(s==0)
            printf("Process exists and we can send if a signal.\n");
      
     
     return 0;
}
