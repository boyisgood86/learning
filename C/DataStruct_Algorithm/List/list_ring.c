
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define _DEBUG	(1)

#if _DEBUG
#define DEBUG(fmt, arg...)	do{printf(fmt, ##arg);}while(0)
#else
#define DEBUG(fmt, arg...)	do {} while(0)
#endif


enum
{
	ok = 1,
	err = 0,
	true = 1,
	false = 0,
};


typedef int Data;
typedef struct Node Node;
typedef int bool;
struct Node
{
	Node * pNext;
	Data data;
};

int list_print(Node *pHead)
{
	if(!pHead) {
		DEBUG("phead is null !\n");
		return err;
	}

	Node * p = pHead->pNext;
	while(p){
		printf("data = %d\n",p->data);
		p = p->pNext;
	}

	return ok;
}

int list_create(Node *pHead, Node *node)
{
	if(!pHead){
		DEBUG("head is null!\n");
		return err;
	}
	
	Node *p = pHead->pNext;
	Node *q = pHead;
	while(p){
		q = p;
		p = p->pNext;
	}
	node->pNext = p;
	q->pNext = node;

	return ok;
}

int list_print_loop(Node *pHead, Node *entry_addr)
{
	if(!pHead){
		DEBUG("head is null !\n");
		return err;
	}
	
	if(!entry_addr){
		DEBUG("No entry addrss !\n");
		return err;
	}

	Node *p = pHead->pNext;
	int flag = 0;
	
	while(p){
		if(p == entry_addr){
			if(flag == 0)
				flag = 1;
			else
				break;
		}
		printf("data = %d\n",p->data);
		p = p->pNext;
	}

	return ok;
}

int list_loop_free(Node *pHead, Node *entry_addr)
{
	if(!pHead){
		DEBUG("head is NULL !\n");
		return err;
	}
	if(!entry_addr){
		DEBUG("entry addr is NULL !\n");
		return err;
	}

	Node *p = pHead;
	Node *q = NULL;
	int flag = 0;
	while(1){
		if(p == entry_addr){
			if(flag == 0){
				flag = 1;
			}else
				break;
		}
	  q = p->pNext;
	  free(p);
	  p = q;
	  DEBUG("==============\n");
	}

	return ok;
}

Node* list_find_ring_entry(Node *pHead)
{
	if(!pHead){
		DEBUG("head is null !\n");
		return NULL;
	}
	Node * fast = pHead;
	Node * slow = pHead;
	while(slow){
		fast = fast->pNext->pNext;
		if(fast == slow)
			break;
		slow = slow->pNext;
	}
	
	Node * temp = slow;
	fast = pHead;
	int length = 0;
	while(1){
		slow = slow->pNext;
		if(slow == fast)
			break;
		if(slow == temp){
			fast = fast->pNext;
			length++;
		}
	}
	printf("loop list entry data is %d\n",fast->data);
	printf("far away head is %d\n",length);

	slow = NULL;
	return fast;
}


int list_check_ring(Node *pHead)
{
	if(!pHead){
		DEBUG("head is null !\n");
		return false;
	}

	Node *fast = pHead;
	Node *slow = pHead;
	while(slow){
		fast = fast->pNext->pNext;
		if(fast == slow)
			return true;
		slow = slow->pNext;
	}
	return false;
}


Node *list_ring(Node *pHead, Node *node, int ring_point)
{
	if(!pHead) {
		DEBUG("head is null !\n");
		return (Node*)NULL;
	}

	Node * p = pHead->pNext;
	Node *q = pHead;

	int ring = 0;

	while(p){
		q = p;
		p = p->pNext;
		ring++;
	}
	if(ring <= ring_point){
		DEBUG("Can't do a ring list , list lenght is shorted than ring_point !\n");
		return pHead;
	}
	q->pNext = node;
	
	p = pHead->pNext;
	int i = 0;
	for(i = 0; i < ring_point && p; i++)
		p = p->pNext;
	node->pNext = p;

	return pHead;
}


int main(int argc, char **argv)
{
	Node *head = (Node*)malloc(sizeof(Node));
	if(!head){
		DEBUG("malloc head faild !\n");
		return -1;
	}

	int i = 0;
	Data data = 0;
	for(i = 0; i < 9; i++) {
		Node * node = (Node*)malloc(sizeof(Node));
		if(!node) {
			DEBUG("malloc node faild !\n");
			return -1;
		}
		node->pNext = NULL;
		node->data = data;
		data += 2;

		list_create(head, node);
	}

	list_print(head);
	
	Node * node = (Node*)malloc(sizeof(Node));
	if(!node){
		DEBUG("mallo new node faild !\n");
		return -1;
	}
	node->pNext = NULL;
	node->data = 100;
	
	list_ring(head, node, 5);
	if(list_check_ring(head) == true){
		DEBUG("Yes, this list is loop !\n");
	}else
		DEBUG("No, this list is not loop !\n");
	
	Node * entry = list_find_ring_entry(head);
	if(!entry){
		DEBUG("Can't find the entry of loop list!\n");
	}else
		DEBUG("find over !\n");

	list_print_loop(head, entry);
	if(list_loop_free(head, entry) == ok){
		head = NULL;
		DEBUG("free list success !\n");
	}

	return 0;
}

