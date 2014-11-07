#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#pragma pack(2)

typedef struct cmd_str
{
	unsigned char cmd;
	unsigned char cluster_id;
}cmd_t;

typedef struct address_str
{
	unsigned short int nwk_dest;
	unsigned char mac[8];
}addr_t;


typedef struct color_str
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
}color_t;

typedef struct value_str
{
	union {
	  unsigned char device_progress;
	  color_t rgb;
	}val;
	unsigned char reserved[4];
}value_t;

typedef struct device_list
{
	/*next*/
	struct device_list *p_next;
	/*device type*/
	unsigned char type;
	/*operation cmd*/
	cmd_t cmd;
	/*device value*/
	value_t val;
	/*device address*/
	addr_t addr;
}List;


int main(void)
{
	List devices;
	addr_t addr;
	/*operation cmd*/
	cmd_t cmd;
	/*device value*/
	value_t val;

	printf("addr = %d\n", (int)sizeof(addr));
	printf("cmd = %d\n", (int)sizeof(cmd));
	printf("val = %d\n", (int)sizeof(val));
	printf("devices = %d\n",(int)sizeof(devices));
	return 0;
}



