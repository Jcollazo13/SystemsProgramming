// Jonathan Collazo || CSCE 3600.501 || EUID: 11535014
// Client side implementation of "ping" utility

#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]) {
  // Check number of arguements given
  if (argc == 2) {
    perror("Missing port number.\nExiting program...\n");
    exit(1);
  }
  if (argc == 1) {
    perror("Missing host name.\nExiting program...");
    exit(1);
  }
  if (argc > 3) {
    perror("Too many arguments provided.\nExiting program...");
    exit(1);
  }

  char *hostname = argv[1];
  int port = atoi(argv[2]);

  struct hostent *server = gethostbyname(hostname);
  if (server == NULL) {
    perror("Host could not be found.\n");
    exit(1);
  }

  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("Failed to create socket.");
    exit(1);
  }

  struct sockaddr_in serveraddr;
  memset(&serveraddr, 0, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(port);
  bcopy((char *)server->h_addr, (char *)&serveraddr.sin_addr.s_addr,
        server->h_length);

  int count = 0;
  int received = 0;
  double rtt_min = 1000000.0;
  double rtt_max = 0.0;
  double rtt_total = 0.0;

  for (int i = 0; i < 10; i++) {
    count++;

    char message[BUFSIZE];
    sprintf(message, "PING %d", i);

    struct timeval start_time, end_time, elapsed_time;
    gettimeofday(&start_time, NULL);

    int n = sendto(sockfd, message, strlen(message), 0,
                   (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (n < 0) {
      perror("Failed to send message.");
    }

    char buffer[BUFSIZE];
    socklen_t serverlen = sizeof(serveraddr);
    n = recvfrom(sockfd, buffer, BUFSIZE, 0, (struct sockaddr *)&serveraddr,
                 &serverlen);

    if (n < 0) {
      printf("Timeout for message %d\n", count);
    } else {
      gettimeofday(&end_time, NULL);
      timersub(&end_time, &start_time, &elapsed_time);
      double rtt = elapsed_time.tv_sec * 1000.0 + elapsed_time.tv_usec / 1000.0;

      received++;
      rtt_total += rtt;

      if (rtt < rtt_min) {
        rtt_min = rtt;
      }

      if (rtt > rtt_max) {
        rtt_max = rtt;
      }

      printf("Received response to message %d (RTT = %.3f ms)\n", count, rtt);
    }

    sleep(1);
  }

  double loss_rate = (count - received) * 100.0 / count;

  printf("Sent = %d, Received = %d, Lost = %d (%.1f%% loss rate)\n", count,
         received, count - received, loss_rate);
  printf("RTT (min/avg/max) = %.3f/%.3f/%.3f ms\n", rtt_min,
         rtt_total / received, rtt_max);

  close(sockfd);
  return 0;
} // End main
