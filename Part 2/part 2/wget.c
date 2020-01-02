#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>          
#include <stdio.h>   
#include <sys/socket.h>
#include <signal.h> 
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

#define PORT 80 
#define BUFMAX  1024

int main(int argc, char* argv[])
{ 
 struct sockaddr_in* saddr;
  char buffer[BUFMAX];
  struct sockaddr_in cli_name; 
  int sock, bytes_read;
  char* url;
  char* start="http://";
  struct addrinfo* res;
  char hostname[100];
  char path[100];

 if (argc != 2) {
    perror("Usage: hostnamelookup <hostname>\n");
    exit(1);
  }
  url = argv[1];

//this string is check if the url have the start of //http:
  if (strncmp(url, start, 7) != 0) {
    printf("err -this is not an http ");
    exit(1);
  }

//this scaf is that take the and delete the http

 sscanf(url, "http://%99[^/]/%99[^\n]", hostname, path);

 //check the name of the host name url
  if (0 != getaddrinfo(hostname, NULL, NULL, &res)) {
    fprintf(stderr, "err -the host name is not up %s\n", hostname);
    exit(1);
  }

  //make a socket that save the protocol
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    { perror ("err-socket cant open");
      close(sock);
      exit(1);
    }

  printf("Client is alive and establishing socket connection.\n");


  saddr = (struct sockaddr_in*)res->ai_addr;

//take the buffer and clean it 
  bzero(&cli_name, sizeof(cli_name)); 
  // use IPv4.
  cli_name.sin_family = AF_INET;  
  cli_name.sin_addr.s_addr = inet_addr(inet_ntoa(saddr->sin_addr)); 
  cli_name.sin_port = htons(PORT);

    //do the connection of the the server to the url
    if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
    { perror ("err-cant connect");
      close(sock);
      exit(1);
    }
    //take the data that givven and do this in the buffer 
    sprintf(buffer, "GET %s%s HTTP/1.0\n\n", hostname, path);
    //send the data to the server
    send(sock, buffer, strlen(buffer), 0);

    do
    {
       //clean the buffer 
        bzero(buffer, sizeof(buffer));
       //fill the bytes_read with data 
        bytes_read = recv(sock, buffer, sizeof(buffer), 0);
        if ( bytes_read > 0 )
            printf("%s", buffer);
    }
    while ( bytes_read > 0 );
    printf("Exiting now.\n");

  close(sock); 
  exit(0);

}