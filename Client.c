#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

  /*make the socket id*/
  int socket_fd;

  /*make struct that will be the socket dest*/
  struct sockaddr_in  dest;

  struct hostent *hostptr;
  char sendmessage[]="Hello from yair and uriel.";
  char getmessage[256]={0};

  struct { char head; u_long body; char tail; } msgbuf;

/*make socket to do communication with the server*/
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

  bzero((char *) &dest, sizeof(dest)); /* They say you must do this */

  /*in argv[1] have the new host name take it and get the host by the name */
  hostptr = gethostbyname(argv[1]);

  /*take the adress and define it by the socket*/
  dest.sin_family = (short) AF_INET;
  bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);
  dest.sin_port = htons((u_short)0x3333);


/*make the messege that look like <msg>*/
  msgbuf.head = '<';
  msgbuf.body = htonl(getpid()); /* IMPORTANT! */
  msgbuf.tail = '>';

  int len = sizeof(dest);
/* make a app that take the msg and send it by the socket dest*/
  sendto(socket_fd,sendmessage,sizeof(sendmessage),0,(struct sockaddr *)&dest,len);

  int n =0;
/*function that return the len of msg*/ 
  n=recvfrom(socket_fd,getmessage,sizeof(getmessage),0,(struct sockaddr *)&dest,&len);
  getmessage[n]='\0';
  printf("Server : %s",getmessage);

  return 0;
}

