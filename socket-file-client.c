#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *errMessage);

int main(int argc, char *argv[])
{
        int sock;
        char errMessage[BUF_SIZE];
        char message[BUF_SIZE];
        int str_len, recv_len, recv_cnt;
        struct sockaddr_in serv_adr;

        if(argc!=4) {
                printf("Usage : %s <IP> <port> <fileName>\n", argv[0]);
                exit(1);
        }

        sock=socket(PF_INET,SOCK_STREAM,0);
        if(sock==-1)
                error_handling("socket() error");

        memset(&serv_adr, 0, sizeof(serv_adr));
        serv_adr.sin_family = AF_INET;
        serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
        serv_adr.sin_port=htons(atoi(argv[2]));

        if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
                error_handling("connect() error!");

        else
                puts("Connected..............");

        FILE* fp = fopen(argv[3], "r");
        if(fp == NULL) printf("file open error!");

        int ch;
        while((ch = fgetc(fp))!=EOF)
        {
                fgets(message, BUF_SIZE, fp);
                str_len = write(sock, argv[3], strlen(argv[3])+1); 
                // argv[3]에서 strlen+1만큼의 데이터를 sock에 작성하는 것을 str_len에 저장

                recv_len = 0;
                while(recv_len<str_len) // 전송한 데이터의 크기만큼 read 함수 반복 호출
                {
                        recv_cnt = read(sock, &message[recv_len], BUF_SIZE-1);
                        if(recv_cnt==-1)
                                error_handling("read() error!");
                        recv_len+=recv_cnt;
                }   
        }
        close(sock);
        return 0;
}


void error_handling(char *errMessage)
{
        fputs(errMessage, stderr);
        fputc('\n', stderr);
        exit(1);
}

