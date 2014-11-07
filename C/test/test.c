#include <stdio.h>
#include <string.h>

int main(void)
{
	char buff[8] = {0};
	char B[8] = {0x01};

	printf("%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X\n",
			B[0],B[1],B[2],B[3],B[4],B[5],B[6],B[7]);
	memcpy(B, buff, 8);
	printf("%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X\n",
			B[0],B[1],B[2],B[3],B[4],B[5],B[6],B[7]);
	return 0;
}


