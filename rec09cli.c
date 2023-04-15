// compile: gcc rec09cli.c -o rec09cli
// usage  : ./rec09cli port

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int sockfd = 0, n = 0, portno;
  char recvBuff[1025];
  struct sockaddr_in serv_addr;

  memset(recvBuff, '0', sizeof(recvBuff));
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("socket error\n");
    exit(EXIT_FAILURE);
  }

  serv_addr.sin_family = AF_INET;
  portno = atoi(argv[1]);
  serv_addr.sin_port = htons(portno);
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (connect(sockfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("connect error\n");
    exit(EXIT_FAILURE);
  }

  while ((n = read(sockfd, recvBuff, sizeof(recvBuff) - 1)) > 0) {
    recvBuff[n] = 0;
    if (fputs(recvBuff, stdout) == EOF) {
      printf("fputs error\n");
    }
  }

  if (n < 0) {
    printf("read error\n");
  }

  return 0;
}
