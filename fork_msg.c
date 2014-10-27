#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



#define _DEBUG	(1)

#if _DEBUG
#define DEBUG(arg, fmt...)	 printf(arg, ##fmt);
#else
#define DEBUG(arg, fmt)	
#endif /*_DEBUG*/


#define MAX_LEN		(1024)
#define MSG_KEY   (10240)

typedef struct msgstru
{
	long int msg_type;
	char msg_buff[MAX_LEN];
}msg_t;


void msg_recv()
{
	DEBUG("%s,%d\n",__func__,__LINE__);
	/*take a msg id*/
	int msg_id = msgget((key_t)MSG_KEY, 0666|IPC_CREAT);
	printf("recv msg id = %d\n",msg_id);
	if(msg_id < 0) {
		DEBUG("%s,%d\n",__func__,__LINE__);
		perror("msgget");
		return ;
	}

	msg_t msg;
	memset(&msg, 0, sizeof(msg));
	/*read data from msg queue, if "over" break;*/
	while(1){
		int recv_value = msgrcv(msg_id, (void*)&msg, (size_t)sizeof(msg_t), 0,0);
		if(recv_value == -1) {
			DEBUG("%s,%d\n",__func__,__LINE__);
			perror("msgrcv");
			return ;
		}
		printf("recv data is [%s]\n",msg.msg_buff);
		break ;
	}

	int rm_value = msgctl(msg_id, IPC_RMID, 0);
	if(rm_value < 0) {
		perror("msgctl");
		return ;
	}

	return ;
}


void msg_send()
{
	DEBUG("%s,%d\n",__func__,__LINE__);
	/*take a msg id*/
	int msg_id = msgget((key_t)MSG_KEY, 0666|IPC_CREAT);
	printf("send  msg_id = %d\n",msg_id);
	if(msg_id < 0) {
		DEBUG("%s,%d\n",__func__,__LINE__);
		perror("msgget");
		return ;
	}

	msg_t msg;
	memset(&msg, 0, sizeof(msg));
	msg.msg_type = 1;
	
	/* write */
	memcpy(msg.msg_buff, "Hello boy !", 12);
	int send_value = msgsnd(msg_id, (void *)&msg, (size_t)strlen(msg.msg_buff), 0);
	if(send_value < 0) {
		DEBUG("%s,%d\n",__func__,__LINE__);
		perror("msgsnd");
		return ;
	}

	return ;
}

int main(void)
{
	msg_send();
	pid_t p = fork();
	if(p == 0)
		msg_recv();
	else if(p < 0)
		exit(-1);

	DEBUG("%s,%d\n",__func__,__LINE__);
	exit(0);
}


