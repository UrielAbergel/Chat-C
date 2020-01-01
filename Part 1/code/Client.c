#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#define PORT_C 1235
#define PORT_R 1233
int main(int argc, char *argv[])
{
	char name[1024];
	int socket_fd,cc, bin,length;
    struct sockaddr_in serv_ad,dest;
    struct hostent *hostptr;
	socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
	memset((char *) &serv_ad,0,sizeof(serv_ad));
    memset((char *) &dest,0,sizeof(dest));
  	
	serv_ad.sin_family-(short)AF_INET;
	serv_ad.sin_addr.s_addr=(INADDR_ANY);
	serv_ad.sin_port=PORT_C;


	dest.sin_family-(short)AF_INET;
	dest.sin_addr.s_addr=(INADDR_ANY);
	dest.sin_port=PORT_R;

	cc=bind(socket_fd,(struct sockaddr*) & serv_ad,sizeof(serv_ad));
	
	fflush(stdout);
	
	while(1)
		{
		bzero(name,1024);
		fgets(name,1024,stdin);

		if(strcmp(name,"exit\n")==0)

			{
				strcpy(name,"connetion ended \n");
				sendto(socket_fd,&name,1024,0,(struct sockaddr *)&dest,sizeof(dest));
				
				close(socket_fd);
				break;
			}

		sendto(socket_fd,name,1024,0,(struct sockaddr *)&dest,sizeof(dest));
		bzero(name,1024);
		length=sizeof(dest);
		recvfrom(socket_fd,name,1024,0,(struct sockaddr *)&dest,&length);
		printf("%s\n",name);
		fflush(stdout);
		}
		
		return(0);
}
