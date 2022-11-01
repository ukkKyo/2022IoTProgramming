#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define MAXLINE 1024

int main(int argc, char *argv[])
{

  int send_s, recv_s; //  수신 및 송신용 소켓
  int pid;
  unsigned int yes = 1;
  struct sockaddr_in mcast_group; // 멀티캐스트 그룹 주소

  struct ip_mreq mreq;
  char line[MAXLINE];
  char name[10];  //  채팅 참가자 이름
  int n, len;

  if(argc!=4)
  {
    printf("사용법 : %s multicast_address port My_name \n", argv[0]);
    exit(0);
  }
  sprintf(name, "[%s]", argv[3]);

  // 멀티캐스트 수신용 소켓 개설
  memset(&mcast_group, 0, sizeof(mcast_group));
  mcast_group.sin_family = AF_INET;
  mcast_group.sin_port = htons(atoi(argv[2]));
  mcast_group.sin_addr.s_addr = inet_addr(argv[1]);
  if((recv_s=socket(AF_INET, SOCK_DGRAM, 0)) <0)
  {
    printf("error : Can't create receive socket\n");
    exit(0);
  }

  // 멀티캐스트 그룹에 가입
  mreq.imr_multiaddr = mcast_group.sin_addr;
  mreq.imr_interface.s_addr = htonl(INADDR_ANY);
  if(setsockopt(recv_s, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) <0)
  {
    printf("error : add membership\n");
    exit(0);
  }

  // 소켓 재사용 옵션 지정
  if (setsockopt(recv_s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) <0)
  {
    printf("error : reuse setsockopt\n");
    exit(0);
  }

  // 소켓 바인드
  if(bind(recv_s, (struct sockaddr*)&mcast_group, sizeof(mcast_group))<0)
  {
    printf("error : bind receive socket\n");
    exit(0);
  }

  // 멀티캐스트 메시지 송신용 소켓 개설
  if((send_s = socket(AF_INET, SOCK_DGRAM, 0)) <0)
  {
    printf("error : Can't create send socket\n");
    exit(0);
  }

  // fork() 실행 : child는 수신 담당 parent는 송신 담당
  if((pid=fork()) <0)
  {
    printf("error : fork\n");
    exit(0);

  // child process : 채팅 메시지 수신 담당
  } else if(pid == 0)
  {
    struct sockaddr_in from;
    char message[MAXLINE+1];
    for(;;)
    {
      printf("receiving message...\n");
      len = sizeof(from);
      if((n=recvfrom(recv_s, message, MAXLINE, 0, (struct sockaddr*)&from, &len)) < 0)
      {
        printf("error : recvfrom\n");
        exit(0);
      }

      message[n] = 0;
      printf("Received Message : %s\n", message);
    }

  // parent process : 키보드 입력 및 메시지 송신 담당
  } else
    {
      char message [MAXLINE + 1], line[MAXLINE + 1];
      printf("Send Message : ");
      while (fgets(message, MAXLINE, stdin) != NULL)
      {
        sprintf(line, "%s %s", name, message);
        len = strlen(line);
        if(sendto(send_s, line, strlen(line),0,(struct sockaddr*)&mcast_group, sizeof(mcast_group)) < len)
        {
          printf("error : sendto\n");
          exit(0);
        }
      }
    }
  }
