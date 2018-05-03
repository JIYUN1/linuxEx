#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

int main(void)
{  
   int fd;
   char temp[100];
   char rbuf[100];
   int wcount, rcount, pos;
   
   //144p
   fd = open("./test.txt", O_RDWR | O_CREAT | O_TRUNC, \
         S_IXUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IROTH);
          //usr w권한, uur, R권한, 그룹 R권한, others R권한
 //TRUNC: test.txt가 있으면 공백으로 WRONLY 특성으로  하나 만듬 (기존파일 무시)
 
  if(fd == -1)
  {
     printf("file open error!!\n");
     return -1;
  }
   
   //버퍼에 테스트 문자열 만들기
   sprintf(temp, "Do not count the before they hatch.");
    
  
  //test.txt 파일에 문자열 쓰기 
   wcount = write(fd, temp, strlen(temp));
 

 //파일에 쓴 문자열 갯수 출력

   printf("wcount=%d\n", wcount);
 
 //파일내의 커서 위치를 시작점 기준으로 offset 0번지로 이동

   pos = lseek(fd, 17, SEEK_SET);   
   write(fd, "eggs ", strlen("eggs "));

 // lseek(fd, offset, SEEK_END); offset -값
 // lseek(fd, offset, SEEK_CUR); 커서 위치 어디로 이동할지 기준점 달라짐
 //lseek로 정상적으로 이동되었는지 확인 
   printf("pos=%d\n", pos);   
   
   pos = lseek(fd, 0, SEEK_SET);
//파일 읽기 -> rbuf에 채움
   rcount = read(fd, rbuf, BUFSIZE);
//읽은 문자열 갯수를 확인
   printf("rcount=%d\n", rcount);

//읽은 버퍼의 내용 확인 
   printf("rbuf : %s\n", rbuf);
   printf("fd=%d\n", fd);

 //파일 닫기
   close(fd);


  fd = creat("./test2.txt", 0764);

  if(fd == -1)
  {
     printf("file creat error!!\n");
     return -1;
  }



   
  close(fd);
  

  //printf("fd=%d\n",fd);
// 반납했던 거 다시 가져와서 둘다 3
  return 0;

}
