#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ym_json.h"


int main(void)
{
	int i = 0;
	js_root_t json;
#if 0
	memset(&json, 0, sizeof(json));

	/* init*/
	json.body = 1;
	json.head = 1;

	/*body*/
	json.ym_body.list = 1;
	json.ym_body.user = 1;
	json.ym_body.other = 1;
	memcpy(json.ym_body.ym_user.name, "Harry boot",8);
	memcpy(json.ym_body.ym_user.passwd, "Harry boot",8);
	json.ym_body.ym_list.ym_dev = (js_dev_t*)malloc(10);
	if(!json.ym_body.ym_list.ym_dev) {
		printf("%s,%d: malloc dev space faild !\n",__func__,__LINE__);
	}else {
		memset(json.ym_body.ym_list.ym_dev, 0, 10);
		json.ym_body.ym_list.size = 10;
		json.ym_body.ym_list.flag = YM_OBJECT;
		for(i = 0; i < 10; i++){
			memcpy((json.ym_body.ym_list.ym_dev+i)->device_mac, "hhhhhhhhhhhhhhhhhhhhhhdd",25);
			(json.ym_body.ym_list.ym_dev+i)->devcice_progress = i;
		}
	}
	/*head*/
	json.ym_head.method = 100;
	json.ym_head.status = 100;
	memcpy(json.ym_head.mobileid, "1234567890123456789",18);
	memcpy(json.ym_head.boxid, "1234567890123456789",18);

	/*malloc*/
	char *buff = (char*)malloc(1024);
	if(!buff) {
		printf("%d: malloc faild !\n\r",__LINE__);
		return -1;
	}
	if(ym_json_creat(&json, buff) < 0) {
		printf("%d: create faild !\n",__LINE__);
		free(buff);
		return -1;
	}
#endif
//	char *s ="{\"body\":{\"list\":[\"admin\",\"admin11\",\"admin22\"],\"other\":{\"isAuthority\":true},\"user\":{\"name\":\"admin\",\"password\":\"admin\"}},\"head\":{\"method\":1000,\"mobileid\":\"353714986786243\",\"status\":0}}" ;
	char *s ="{\"body\":{\"list\":[{\"device_mac\":\"11:22:33:44:55:66:77:88\",\"dev_progress\":100}],\"other\":{\"isAuthority\":true},\"user\":{\"name\":\"admin\",\"password\":\"admin\"}},\"head\":{\"method\":1000,\"mobileid\":\"353714986786243\",\"status\":0}}" ;

	memset(&json, 0, sizeof(json));
	json.head = 1;
	json.body = 1;
	json.ym_body.list = 1;
	json.ym_body.user = 1;
	json.ym_body.other = 1;
	json.ym_body.ym_list.flag = YM_OBJECT;

	if(ym_json_parsel(&json, s)<0){
		printf("%s,%d: parsel faild !\n",__func__,__LINE__);
	}
	/*test head*/
	printf("method = %d\n",json.ym_head.method);
	printf("status = %d\n",json.ym_head.status);
	printf("mobileid = %s\n", json.ym_head.mobileid);
	printf("boxid = %s\n", json.ym_head.boxid);
	printf("message = %s\n", json.ym_head.message);
	/*test user*/
	printf("name = %s\n", json.ym_body.ym_user.name);
	printf("passwd = %s\n", json.ym_body.ym_user.passwd);
	printf("new passwd = %s\n", json.ym_body.ym_user.new_passwd);
	/*other*/
	printf("isAuthority = %d\n",json.ym_body.ym_other.isAuthority);
	/*list*/
	printf("size = %d\n",json.ym_body.ym_list.size);
	printf("mac = %s\n",json.ym_body.ym_list.ym_dev->device_mac);
	printf("progress = %d\n",json.ym_body.ym_list.ym_dev->devcice_progress);

#if 0
	printf("%d:%s\n",__LINE__,buff);

	if(buff)
		free(buff);
#endif
	if(json.ym_body.ym_list.ym_dev)
		printf("no free..\n");
//		free(json.ym_body.ym_list.ym_dev);

	return 0;
}


