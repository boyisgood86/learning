#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define		SOCKET_FA		(-100)
#define		IP_VALUE		(-101)
#define		BIND_FA			(-102)
#define		LISTEN_FA		(-103)
#define		ACCEPT_FA		(-104)


#define		PORT			(9999)
#define		IPADD			("192.168.1.49")


int main(int argc, char **argv)
{
	int listenfd = 0;
	int confd = 0;
	int i = 0;
	int opt;
	socklen_t len;
	struct sockaddr_in	server_addr , client_addr;
	fd_set	readset;
	struct timeval timeout;

	if( (listenfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0) {
		perror("socket:");
		return SOCKET_FA;
	}
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);

	if( inet_pton(AF_INET, IPADD, &server_addr.sin_addr) < 0){
		perror("ip error:");
		return IP_VALUE;
	}

	
	if( bind(listenfd, (struct sockaddr*)&server_addr, (socklen_t)sizeof(server_addr)) < 0) {
		perror("bind:");
		return BIND_FA;
	}

	if( listen(listenfd, 0) < 0){
		perror("listen");
		return LISTEN_FA;
	}

	fd_set readset, allset;
	int maxfdp;
	int ret;
	struct timeval timeout;

	FD_ZERO(&readset);
	FD_ZERO(&allset);
	FD_SET(liostenfd, &readset);
	maxfdp = listenfd;

	while (1) {
		if( (confd = accept(listenfd, (struct sockaddr*)&client_addr, &len) ) < 0)
		{
			perror("accept");
			continue ;
		}
		close(confd);
	}
	return 0;
}

