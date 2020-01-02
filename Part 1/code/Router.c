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
#include <string.h>
#include <stdlib.h>

#define PORT_C 1235
#define PORT_S 1234
#define PORT_R 1233

void printsin(struct sockaddr_in *sin, char *pname, char* msg)
{
    char *ip = inet_ntoa(sin->sin_addr);
    puts(pname);
    printf("%s ip= %s, port= %d\n", msg, ip, sin->sin_port);
}

double Rand()
{
	return(double)rand()/(double)RAND_MAX;
}

int main(int args,char *argv[]){
	double random;
	double x,y;
	printf("enter your choice \n");
	scanf("%lf", &y);
	printf("%f\n",y);
	char name[1024];
	int socket_fd,bind_fd,recv,fsize;
	struct sockaddr_in serv_ad,from, destA, destC;
	
	socket_fd=socket(AF_INET,SOCK_DGRAM,0);
	memset((char *) &serv_ad,0,sizeof(serv_ad));
	memset((char *) &from,0,sizeof(from));
	memset((char *) &destA,0,sizeof(destA));
	memset((char *) &destC,0,sizeof(destC));

	serv_ad.sin_family=(short)AF_INET;
    serv_ad.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_ad.sin_port=PORT_R;

	destA.sin_family=(short)AF_INET;
    destA.sin_addr.s_addr = htonl(INADDR_ANY);
    destA.sin_port=PORT_C;

	destC.sin_family=(short)AF_INET;
    destC.sin_addr.s_addr = htonl(INADDR_ANY);
    destC.sin_port=PORT_S;
	
	bind_fd=bind(socket_fd,(struct sockaddr *) &serv_ad,sizeof(serv_ad));


	while(1)
	{

	fsize=sizeof(from);
	bzero(name,1024);
	recv=recvfrom(socket_fd,name,1024,0,(struct sockaddr *)&from,&fsize);
	printsin(&from, "recv_udp: ", " Packet from:");
	puts(name);
	fflush(stdout);
	if(from.sin_port==PORT_C)

		{
			random=Rand();

			if (random>x)
			sendto(socket_fd,name,1024,0,(struct sockaddr *)&destC,sizeof(destC));

			else {
			strcpy(name,"messege lost\n");
			sendto(socket_fd,name,1024,0,(struct sockaddr *)&destA,sizeof(destA));
			}
		}
				
		else
		sendto(socket_fd,name,1024,0,(struct sockaddr *)&destA,sizeof(destA));
		
	
	}
return 0;
}
