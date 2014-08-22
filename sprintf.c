#include <stdio.h>
#include <string.h>

int main(void)
{
	char *s = "Hello world";
	char buff[20];
	memset(buff, 0, sizeof(buff));

	if(sprintf(buff, "%s",s) < 0) {
		perror("sprintf");
		return -1;
	}
	printf("%s\n",buff);
	return 0;
}

