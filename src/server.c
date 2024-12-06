#include "server.h"
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>

void *handle_client(void *arg);

void create_server(int port) {
  int sockfd, client_sock;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_len = sizeof(client_addr);

  // Creating Socket
  sockfd = socket(AF_INET , SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("Error creating socket");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);
  server_addr.sin_family = AF_INET;

  // Binding it
  printf("Binding a socket... \n");
  if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
    perror("Error in binding");
    close(sockfd);
    exit(EXIT_FAILURE);
  };

  // Listen
  printf("Listening for connections... \n");
  if (listen(sockfd, 5) < 0) {
    perror("Error in Listen");
    close(sockfd);
    exit(EXIT_FAILURE);
  }

  // Accept
  printf("Aceppting connections \n");

  while (1) {
    client_sock = accept(sockfd, (struct sockaddr *) &client_addr, &client_len);
    if (client_sock < 0) {
      perror("Aceppt failed");
      continue;
    }
    
    // Create new thread to handle Request
    int *client_sock_ptr = malloc(sizeof(int));
    client_sock_ptr = &client_sock;
    pthread_t thred_id;
    pthread_create(&thred_id, NULL , handle_client, (void*) client_sock_ptr);
    pthread_detach(thred_id);

  }
  // Close sockets
  close(client_sock);
  close(sockfd);

}

void *handle_client(void *arg) {
  int client_sock = *(int *)arg;
  char buffer[1024] = {0};

  int n = recv(client_sock, buffer, sizeof(buffer), 0);
  // If bytes receive > 0  
  if (n > 0) {

      printf("\nReceived: %s\n", buffer);
      // parse_http_method(buffer);
      // handler(method m, ); 
      
     
      // sending response for client    
      char *response =
          "HTTP/1.1 200 OK\r\n"
          "Content-Type: text/plain; charset=utf-8\r\n"
          "Content-Length: 13\r\n"
          "Connection: close\r\n"
          "\r\n"
          "Hello, World!";

      send(client_sock, response, strlen(response), 0);
    }

  close(client_sock);
  return NULL;
}
