#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#define SIM_LENGTH 10 
#define PORT 1337 

int main(int argc, char* argv[])
{ 
   /* Define the variables*/
  struct addrinfo* res;
  char* hostname;
  char* hostaddr;
  struct sockaddr_in* saddr;
  int sock; 
  struct sockaddr_in cli_name; 
  int count;
  int value; 

  /* Check if he recive hostname */
  if (argc != 2) {
    perror("Usage: net_client.o <hostname>\n");
    exit(1);
  }

  /*Insert the hostname he get into string*/
  hostname = argv[1];
  
  /* Get the ip address by hostname string*/
  if (0 != getaddrinfo(hostname, NULL, NULL, &res)) {
    fprintf(stderr, "Error in resolving hostname %s\n", hostname);
    exit(1);
  }

  /* Resolve host address as string*/
  saddr = (struct sockaddr_in*)res->ai_addr;
  hostaddr = inet_ntoa(saddr->sin_addr);

  printf("Client is alive and establishing socket connection.\n");
  
  
  /*struct the socket*/
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    { perror ("Error opening channel");
      close(sock);
      exit(1);
    }
      

 /*Defaine the socket*/
  memset((char *)&cli_name,0, sizeof(cli_name));  
  cli_name.sin_family = AF_INET; 
  cli_name.sin_addr.s_addr = inet_addr(hostaddr); 
  cli_name.sin_port = htons(PORT);


  /* Connect the socket, and check if it succeeded*/
  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
    { perror ("Error establishing communications");
      close(sock);
      exit(1);
    }

  for (count = 1; count <= SIM_LENGTH; count++)
    { 
      /*Write the values he gets from the socket */
      read(sock, &value, 4);
      printf("Client has received %d from socket.\n", value);
    }

  printf("Exiting now.\n");
  close(sock); 
  exit(0); 

} 