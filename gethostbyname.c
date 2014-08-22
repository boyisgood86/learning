
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFF_SIZE		(256)

#define _DEBUG

#ifdef _DEBUG
#define DEBUG(fmt, arg...)	do{printf(fmt,##arg);}while(0)
#else
#define DEBUG(fmt, arg...)	do{//TODO..}while(0)
#endif /* DEBUG */

// http://www.cnblogs.com/boymgl/articles/1664331.html

/*
   struct hostent {   
   char *h_name; 		 //表示的是主机的规范名。例如www.google.com的规范名其实是www.l.google.com 
   char **h_aliases;   	//表示的是主机的别名。www.google.com就是google他自己的别名。有的时候，有的主机可能有好几个别名
   int h_addrtype;   	//主机ip地址的类型，到底是ipv4(AF_INET)，还是ipv6(AF_INET6)
   int h_length;   		//表示的是主机ip地址的长度
   char **h_addr_list;   //表示的是主机的ip地址，注意，这个是以网络字节序存储的
   };

 */


int main(int argc, char **argv)
{
	char **p;
	char buff[BUFF_SIZE];
	struct hostent *host;
	if(argc < 2) {
		DEBUG("Usage: a.out www.google.com.hk\n");
		return -1;
	}
	/* gethostbyname */
	if( !(host = gethostbyname(argv[1]))) {
		DEBUG("%s, %d: get host faild from \"%s\" \n",__func__,__LINE__,argv[1]);
		return -1;
	}
	
	/*host name*/
	DEBUG("%s, %d: host name is : %s\n",__func__,__LINE__,host->h_name);
	
	/* host other name */
	for(p = host->h_aliases; *p != NULL; p++){
		DEBUG("%s, %d: host aliases name is %s\n",__func__,__LINE__,*p);
	}
	
	/* address */
	memset(buff, 0, sizeof(buff));
	if(host->h_addrtype == AF_INET || host->h_addrtype == AF_INET6) {
		for(p = host->h_addr_list; *p != NULL; p++) {
			DEBUG("%s, %d: address is : %s\n",__func__,__LINE__,inet_ntop(host->h_addrtype, *p, buff, sizeof(buff)));
		}
	}else {
		DEBUG("%s, %d: Unlonwn address..\n",__func__,__LINE__);
	}
	DEBUG("\n");
	return 0;
}
