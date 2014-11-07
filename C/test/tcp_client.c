#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define		DEBUG				(1)
#define		OP_FA				(-99)
#define		SOCKET_FA			(-100)
#define		IP_FA				(-101)
#define		CONNECT_FA			(-102)


unsigned char send_buff[16] ;

#define BUFF_LEN	(16)

int main(int argc, char **argv)
{
	struct sockaddr_in server_addr;
	int sockfd = {0};
	int i = 0;
	int read_size = -1;
	unsigned char read_buff[BUFF_LEN] = {0};
	unsigned char * send_string = "Hello world !\n";


	if (argc != 3) {
		printf("Usage: ./client 192.168.142.128 4096\n");
		return OP_FA;
	}

	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
		return SOCKET_FA;
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));
	if( (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) ) < 0) {
		perror("inet_pton");
		return IP_FA;
	}
	while(1) {
		if( connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
			perror("connect");
			printf("%s\n",strerror(errno));
			continue ;
		}
		read_size = read(sockfd, read_buff, BUFF_LEN);
		if(read_size < 0) 
			break;;
		else if(read_size == 0){
			printf("read_size = %d\n", read_size);
			break ;
		}else {
			if(write(confd, send_string, sizeof(send_string)) < 0){
				printf("send faild !\n");
				break ;
			}
		}
	}
	close(sockfd);
	return 0;
}
