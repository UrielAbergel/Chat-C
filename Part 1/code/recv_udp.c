#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
 
void printsin(struct sockaddr_in *sin, char *pname, char* msg) {

  printf("%s\n", pname);
  printf("%s ", msg);
  printf("ip= %s , port= %d", inet_ntoa(sin->sin_addr), sin->sin_port);
  printf("\n");
}

 
int main(int argc, char *argv[])
{
  /*define the socket id and the size of the socket*/
  int socket_fd, cc, fsize;
 /*define struct that will be the socket*/
  struct sockaddr_in  s_in, from;
  char servermessage[]="hello from server.";
  char getmessage[256]={0};
   /*define struct that will be the the messege in the messenger*/
  struct { char head; u_long  body; char tail;} msg;
 

/*Define socket IPv4 of this protocol ,UDP in the type, and protocol and send zero becuase this is defualt */
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
 
  bzero((char *) &s_in, sizeof(s_in));  /* They say you must do this    */
/*define the socket addres that he will communicted later*/
  s_in.sin_family = (short)AF_INET;
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */
  s_in.sin_port = htons((u_short)0x3333);
 
  //printsin( &s_in, "RECV_UDP", "Local socket is:"); 
  fflush(stdout);
 
  /*define the socket addres that he will communicted later*/
  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));
 
  /*infinty loop for the working soucket*/
  for(;;) {
    fsize = sizeof(from);
     /*take the messege and put it in the messge storge */
    cc = recvfrom(socket_fd,getmessage,sizeof(getmessage),0,(struct sockaddr *)&from,&fsize);
    //printsin( &from, "recv_udp: ", "Packet from:");
    getmessage[cc]='\0';
    printf("Client: %s",getmessage); 

    sendto(socket_fd,servermessage,sizeof(servermessage),0,(struct sockaddr *)&from,fsize);
    fflush(stdout);
    printsin(&s_in, "UDP-SERVER:", "Local socket is:");
    printsin((struct sockaddr_in*)&from, "UDP-SERVER: ","Packet from:");
  }
   /*take a socket and connect it to the adress */
  return 0;
}