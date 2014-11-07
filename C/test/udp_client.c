#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
	int sockfd = -1;
	char send_buff[128] = "Hello world !\n";
	char read_buff[128] = {0};
	socklen_t len;
	struct sockaddr_in server_addr, client_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	memset(&client_addr, 0, sizeof(client_addr));
	if(argc != 3) {
		fputs("Usage: ./udpclient 192.168.1.1 37128\n", stdout);
		return -1;
	}
	printf("server ip is %s and port is %d\n", argv[1], atoi(argv[2]));
//	fgets(send_buff, 128, stdin);

	if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0) ) < 0){
		perror("socket");
		return -1;
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons( atoi(argv[2]) );
	if(inet_pton(AF_INET, argv[1], &server_addr.sin_addr) < 0) {
		perror("inet_pton");
		return -1;
	}
	
	while(1) {
		printf("----->\n");
		if( sendto(sockfd, send_buff, sizeof(send_buff), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
			perror("sendto");
			return -1;
		}
		if( recvfrom(sockfd, read_buff, sizeof(read_buff), 0, (struct sockaddr *)&client_addr, &len) == -1) {
			perror("recvfrom");
			return -1;
		}
		fputs(read_buff, stdout);
//		memset(send_buff, 0, 128);
//		fgets(send_buff, 128, stdin);
		sleep(1);
	}
	return 0;
}
