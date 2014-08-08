#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
	struct  sockaddr_in server_addr, client_addr;
	socklen_t len;
	int sockfd = -1;
	char buff[128] = {0};
	char cli_buff[128] = {0};
	memset(&server_addr, 0, sizeof(server_addr));
	memset(&client_addr, 0, sizeof(client_addr));
	
	if (argc != 3) {
		fputs("Usage: udpserver 192.168.1.x 37128\n", stdout);
		return -1;
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons( atoi(argv[2]) );
	if( inet_pton(AF_INET, argv[1], (struct sockaddr*)&server_addr.sin_addr) < 0) {
		perror("inet_pton");
		return -1;
	}

	if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		return -1;
	}
	if( bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		perror("bind");
		return -1;
	}
	while(1) {
		fputs("Now wait....\n", stdout);
		if( recvfrom(sockfd, buff, 128, 0, (struct sockaddr*)&client_addr, &len) == -1) {
			perror("recvfrom");
			return -1;
		}
		fputs("recv msg from:\n", stdout);
		printf("%s, %d\n", inet_ntop(AF_INET, &client_addr.sin_addr, cli_buff, 128), ntohs(client_addr.sin_port));
		fputs(buff, stdout);
		if( sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&client_addr, len) == -1) {
			perror("sendto");
			return -1;
		}

	}
	return 0;
}
