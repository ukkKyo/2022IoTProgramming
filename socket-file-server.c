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
        int serv_sock, clnt_sock;
        char errMessage[BUF_SIZE];
        char message[BUF_SIZE];
        int str_len, i;

        struct sockaddr_in serv_adr;
        struct sockaddr_in clnt_adr;
        socklen_t clnt_adr_sz;

        if(argc!=2) {
                printf("Usage : %s <port>\n", argv[0]);
                exit(1);
        }

        serv_sock = socket(PF_INET, SOCK_STREAM, 0);
        if(serv_sock==-1)
                error_handling("socket() error");

        memset(&serv_adr, 0, sizeof(serv_adr));
        serv_adr.sin_family=AF_INET;
        serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
        serv_adr.sin_port=htons(atoi(argv[1]));

        if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
                error_handling("bind() error");

        if(listen(serv_sock, 5)==-1)
                error_handling("listen() error");

        clnt_adr_sz=sizeof(clnt_adr);

        clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_adr, &clnt_adr_sz);
        if(clnt_sock==-1)
                error_handling("accept() error");
        else
                printf("Connected client %d \n", i+1);

        if(str_len=read(clnt_sock, message, BUF_SIZE)!=0) { // clnt_sock으로부터 BFU_SIZE만큼의 데이터를 읽어서 message에 저장.
                strncpy(message, message, str_len);
                FILE* fp = fopen(message, "w"); // message라는 이름으로 파일 생성하고 open
                while(1){ // 성공적이면
                  fputs(message, fp); // 클라이언트에서 전송하는 데이터를 읽어서 파일에 저장.
                } 
        }
        
        close(clnt_sock);
        close(serv_sock);
        return 0;
}

void error_handling(char *errMessage)
{
        fputs(errMessage, stderr);
        fputc('\n', stderr);
        exit(1);
}