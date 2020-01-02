
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
  /*struct that get all the info*/
  struct addrinfo* res;
  char* hostname;
  char* hostaddr;

  /*struct that will be the socket */
  struct sockaddr_in* saddr;
  
  /*this is throw a messege if that no good adress   */
  if (argc != 2) {
    perror("Usage: hostnamelookup <hostname>\n");
    exit(1);
  }

  hostname = argv[1];
  
  /*if the adress is not a real adress*/
  if (0 != getaddrinfo(hostname, NULL, NULL, &res)) {
    fprintf(stderr, "Error in resolving hostname %s\n", hostname);
    exit(1);
  }
  
  /*find the address and restore it on the structs*/
  saddr = (struct sockaddr_in*)res->ai_addr;
  hostaddr = inet_ntoa(saddr->sin_addr);

  /*print the address*/
  printf("Address for %s is %s\n", hostname, hostaddr);
  exit(0);
}
