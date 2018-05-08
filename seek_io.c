/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2017.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 4-3 */

#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    size_t len;
    off_t offset;
    int fd, ap, j;
    char *buf;
    ssize_t numRead, numWritten;

    if (argc < 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file {r<length>|R<length>|w<string>|s<offset>}...\n",
                 argv[0]);  //인자가 3개 미만 또는 argv[1]이 --help면
                       //usageErr이 표준 에러를 출력한뒤 exit()를 호출해 종료

    //파일을 읽기쓰기 용으로 없는 경우 생성해서 열기
    fd = open(argv[1], O_RDWR | O_CREAT,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH);                     /* rw-rw-rw- */
    //열기 실패
    if (fd == -1)
        errExit("open");
     

   //실행 매개변수 2번째 부터 마지막 매개변수까지 r(R)이 있는지 찾음
    for (ap = 2; ap < argc; ap++) {
        switch (argv[ap][0]) {
        case 'r':   

        case 'R':  
                    //현재 보여지는 오프셋 바이트들을 헥사로 출력
            len = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
      //getLong: arg가 가리키는 문자열을 각각 int나 long으로 변환

            
            buf = malloc(len); //arg문자열 길이만큼 동적할당
            if (buf == NULL)
                errExit("malloc");

            numRead = read(fd, buf, len); //fd가 가리키는 파일에서 읽음
            if (numRead == -1) //byte가 -1일때
                errExit("read");

             //읽은 글자수가 0이면 다 읽은 것으로 간주 파일의 끝임을 출력
            if (numRead == 0) {
                printf("%s: end-of-file\n", argv[ap]);
            } else { //아닐 때
                printf("%s: ", argv[ap]); // r뒤 출력
                for (j = 0; j < numRead; j++) {
                    if (argv[ap][0] == 'r')  //r을 만나면
                        printf("%c", isprint((unsigned char) buf[j]) ?
                                                buf[j] : '?');
          //isprintf -> 프린트 가능인지 판별, 참이면 buf[j], 거짓이면 '?'출력
                    else //만나지 않으면 16진수 출력
                        printf("%02x ", (unsigned int) buf[j]);
                }
                printf("\n");
            }

            free(buf);
            break;

        case 'w':  //매개변수가 w일 경우 argv 2부터 작성
            numWritten = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
            if (numWritten == -1)
                errExit("write"); //에러메세지 출력뒤, exit()호출, 프로그램종료
            printf("%s: wrote %ld bytes\n", argv[ap], (long) numWritten);
                //작성한 문자열, 길이 출력
            break;
     
         //매개변수로 s가 들어온 경우 파일 작성 포인터의 위치를 변경한다.
        case 's':  
            offset = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);

           //단어 길이만큼 포인터 이동 이동 실패시 에러
            if (lseek(fd, offset, SEEK_SET) == -1) 
                errExit("lseek");
            //이동한 단어 출력
            printf("%s: seek succeeded\n", argv[ap]);
            break;

        default: //명령행 인자가 rRws이 아닐 
            cmdLineErr("Argument must start with [rRws]: %s\n", argv[ap]);
           //usagrErr()와 비슷, 프로그램에 넘긴 명령행 인자의 에러를 알려줌
	 }
    }

    if (close(fd) == -1)
        errExit("close");

    exit(EXIT_SUCCESS);
}
