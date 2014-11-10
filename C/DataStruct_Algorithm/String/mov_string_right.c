#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define _DEBUG (1)

#if _DEBUG
#define DEBUG(arg, fmt...)	do{printf(arg,##fmt);}while(0)
#else
#define DEBUG(arg, fmt...)	do{}while(0)
#endif /*_DEBUG*/

enum
{
	ok  = 1,
	err = 0,
};

char *mov_right(char *string, unsigned int step)
{
	if (!string){
		DEBUG("string is nulll !\n");
		return NULL;
	}
	char *s = (char*)malloc(strlen(string)+1);
	memset(s, 0, strlen(string)+1);
	strcpy(s, string);

	char *p = s;
	while(*p != '\0')
		p++;
	p -= 1;
	
	int i = 0;
	for(i = 0; i < step; i++){
		char *s1 = p;
		char temp = *p;
		while(s1 != s){
			*s1 = *(s1-1);
			s1--;
		}
		*s = temp;
	}


	return s;
}


int main(void)
{
	char *s = "Hello boy !";
	printf("string is [ %s ]\n", s);
	s = mov_right(s, 11);
	printf("string is [ %s ]\n", s);
	if(s)
		free(s);

	return 0;
}


