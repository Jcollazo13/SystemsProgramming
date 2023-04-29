// Jonathan Collazo || CSCE 3600.501 || EUID: 11535014
// Server side implementation of "ping" utility

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("No port provided.\n Exiting program...");
    exit(1);
  }

  int port_number = atoi(argv[1]);
  if (port_number < 1024 || port_number > 65535) {
    fprintf(
        stderr,
        "Invalid port number. Port number must be between 1024 and 65535.\n");
    exit(1);
  }

  // create socket
  int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_socket < 0) {
    perror("Could not create socket.");
    exit(1);
  }

  // bind socket to server address and port
  struct sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(port_number);
  if (bind(server_socket, (struct sockaddr *)&server_address,
           sizeof(server_address)) < 0) {
    perror("Failed to bind socket.");
    exit(1);
  }

  // waiting for incoming PING messages
  while (1) {
    char buffer[BUFFER_SIZE];
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);
    int bytes_received =
        recvfrom(server_socket, buffer, BUFFER_SIZE, 0,
                 (struct sockaddr *)&client_address, &client_address_len);
    if (bytes_received < 0) {
      perror("No data recieved.");
      exit(1);
    }

    // send message back to client
    char *response = "PONG";
    if (sendto(server_socket, response, strlen(response), 0,
               (struct sockaddr *)&client_address, client_address_len) < 0) {
      perror(
          "Failed to send data."); // Message could not be sent back to client
    }
  }

  // close socket
  close(server_socket);

  return 0;
}
