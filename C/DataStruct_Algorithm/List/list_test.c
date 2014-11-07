
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#define _DEBUG	(1)

#if _DEBUG
#define DEBUG(arg, fmt...)	printf(arg, ##fmt);
#else
#define DEBUG(arg, fmt...)
#endif


enum
{
	ok = 1,
	err = 0,
};


typedef struct Node
{
	struct Node *pNext;
	int data;
}Node;


int list_print(Node *pHead)
{
	Node *p = pHead;
//	p = p->pNext;
	while(p){
		printf("%d ",p->data);
		p = p->pNext;
	}
	printf("\n");

	return ok;
}


Node* list_turn(Node *pHead)
{
	if(!pHead) {
		DEBUG("list is null !\n");
		goto EXIT;
	}

	Node *p = pHead;
	Node *q = pHead->pNext;
	Node *r = NULL;
	
	p->pNext = NULL;

	while(q){
		r = q->pNext;
		q->pNext = p;
		p = q;
		q = r;
	}

	pHead = p;

	return pHead;

EXIT:
	return NULL;
}


int list_insert(Node *pHead, Node* node)
{
	if(!node){
		DEBUG("node is null !\n");
		goto EXIT;
	}

	Node *p = pHead->pNext;
	Node *q	= pHead;

	if(q->data >= node->data && q == pHead){
		;
	}else{
		while(p){
			q = p;
			p = p->pNext;

			if(q->data <= node->data && p->data >= node->data)
				break;
		}
	}

	node->pNext = q->pNext;
	q->pNext = node;

	return ok;
EXIT:
	return err;
}


int list_create(Node *pHead, Node *node)
{
	if(!node) {
		DEBUG("node is NULL !\n");
		goto EXIT;
	}
	
	Node *p = pHead;
	Node *q = p;
	while(p){
		q = p;
		p = p->pNext;
	}

	q->pNext = node;

	return ok;
EXIT:
	return err;
}


int main(int argc, char **argv)
{
	Node * head = (Node*)malloc(sizeof(Node));
	int data = 1;
	if(!head) {
		DEBUG("malloc head faild !\n");
		return -1;
	}
	memset(head, 0, sizeof(Node));
	/*new node*/
	int i = 0;
	for(i = 0; i < 5; i++){
		Node *node = (Node*)malloc(sizeof(Node));
		if(!node){
			DEBUG("malloc new node  faild !\n");
			goto EXIT;
		}
		node->pNext = NULL;
		node->data = data;
		if(list_create(head, node) == err) {
			DEBUG("list create faild !\n");
			goto EXIT;
		}
		data += 2;
	}

	list_print(head);

	data = 0;

	for(i = 0; i < 5; i++) {
		Node *new = (Node*)malloc(sizeof(Node));
		if(!new) {
			DEBUG("malloc new faild !\n");
			goto EXIT;
		}
		new->pNext = NULL;
		new->data = data;
		list_insert(head, new);
		data += 2;
	}
	list_print(head);
	head = list_turn(head);
	list_print(head);

	return 0;
EXIT:
	return -1;
}


