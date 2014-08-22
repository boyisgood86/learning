#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFF_SIZE		(256)

#define _DEBUG

#ifdef _DEBUG
#define DEBUG(fmt, arg...)	do{printf(fmt,##arg);}while(0)
#else
#define DEBUG(fmt, arg...)	do{//TODO..}while(0)
#endif /* DEBUG */


typedef struct udp_sock {
	char sock_buff[BUFF_SIZE];
	socklen_t sock_len;
	int sockfd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
}udp_sock;

enum VAL {
	TRUE 		= 0,
	ARGC_ERR 	= 10,
	SOCK_FAIL   = 11,
	PTON_ERR	= 12,
	BIND_FAIL	= 13,
	RECV_ERR	= 14,
	GETIP_FAIL	= 15,
	SEND_FAIL	= 16,
};


int main(int argc, char **argv)
{
	char cli_buff[BUFF_SIZE];
	udp_sock sock;
	socklen_t addrlen;

	if(argc != 3) {
		DEBUG("Usage: udpserver 192.168.1.x port\n")	;
		return -ARGC_ERR;
	}

	if( (sock.sockfd = socket(AF_INET, SOCK_DGRAM,0)) < 0) {
		perror("creat socket");
		return -SOCK_FAIL;
	} 

	memset(&(sock.server_addr), 0, sizeof(sock.server_addr));
	memset(&(sock.client_addr), 0, sizeof(sock.client_addr));
	memset(sock.sock_buff, 0, sizeof(sock.sock_buff));

	sock.server_addr.sin_family = AF_INET;
	sock.server_addr.sin_port = htons(atoi(argv[2]));
	if(inet_pton(AF_INET, argv[1], (struct addr*)&sock.server_addr.sin_addr) < 0) {
		perror("inet_pton");
		return -PTON_ERR;
	}

	if(bind(sock.sockfd, 
			(struct sockaddr*)&(sock.server_addr),sizeof(sock.server_addr)) < 0) {
		perror("bind");
		return -BIND_FAIL;
	}
/*get local ip*/
	addrlen = sizeof(sock.server_addr);
	if(getsockname(sock.sockfd, 
				(struct sockaddr *)&(sock.server_addr), &addrlen) < 0) {
		perror("getsockname");
		return -GETIP_FAIL;
	}
	
	memset(cli_buff, 0, sizeof(cli_buff));
	if(sprintf(sock.sock_buff,"%s",
				inet_ntop(AF_INET, &(sock.server_addr.sin_addr), cli_buff, sizeof(cli_buff))) < 0)
	{
		perror("sprintf");
	}
	DEBUG("%s, %d, host ip %s, and it's port is %d\n",__func__,__LINE__,sock.sock_buff,ntohs(sock.server_addr.sin_port));
	DEBUG("Now wait ...\n");
	while(1) {
		sock.sock_len = sizeof(sock.client_addr);
		memset(sock.sock_buff,0,sizeof(sock.sock_buff));
		if(recvfrom(sock.sockfd, 
					sock.sock_buff, sizeof(sock.sock_buff), 0, 
					(struct sockaddr*)&(sock.client_addr),&(sock.sock_len)) < 0) {
			perror("recvfrom");
			return -RECV_ERR;
		}
		memset(cli_buff, 0, sizeof(cli_buff));
		DEBUG("%s,%d: %s send data to here, and it's port is %d\n",__func__,__LINE__,
				inet_ntop(AF_INET, &(sock.client_addr.sin_addr), cli_buff, sizeof(cli_buff)),ntohs(sock.client_addr.sin_port));
		DEBUG("%s,%d: msg is : %s\n",__func__,__LINE__,sock.sock_buff);
		if(sendto(sock.sockfd, 
				sock.sock_buff, sizeof(sock.sock_buff), 
				0, 
				(struct sockaddr*)&(sock.client_addr), sock.sock_len) == -1) 
		{
			perror("sendto");
			return -SEND_FAIL;
		}
	}
	return TRUE;
}



