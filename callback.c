#include "stdio.h"
#include "string.h"
#include <stdlib.h>


typedef void (*p)(void);

p p1;

void print_child(void)
{
	printf("Hello world !\n");
	return ;
}

void print_f(p fun)
{
	p1 = fun;
	if(!p1) {
		return ;
	}
	p1();

	return ;
}



int main(void)
{
	print_f(&print_child);
//	print_f(NULL);
	exit(0);
}
