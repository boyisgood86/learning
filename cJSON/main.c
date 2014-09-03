/* here: 
 * http://blog.sina.com.cn/s/blog_a6fb6cc90101ffme.html
 * http://sourceforge.net/projects/cjson/?source=typ_redirect
 * http://blog.csdn.net/xukai871105/article/details/17094113
 * gcc *.c -g -Wall -l m ---> a.out
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"


#define _DEBUG
#ifdef _DEBUG
#define DEBUG(fmt, arg...)	do{printf(fmt, ##arg);}while(0)
#else
#define DEBUG(fmt, arg...)	do{}while(0)
#endif /*_DEBUG*/

enum {
	size = 1024,
};


/* create a json string */
int create(char * const out)
{

	/* {"body:{"list:["name1","name2"]","other:{"name":"xiaohui"}"}"} */
	cJSON *root, *dir1, *dir2, *dir3, *dir4, *dir5;
	const char *ro = "Root";

	if(!out) {
		DEBUG("out is null..\n");
		goto EXIT;
	}
	/*create json string root*/
	root = cJSON_CreateObject();
	if(!root) {
		DEBUG("get root faild !\n");
		goto EXIT;
	}else DEBUG("get root success!\n");

	{
		cJSON * js_body, *js_list,*js_other;

		const char *const body = "body";
		const char *const list = "list";
		const char *const other = "other";
		const char *const s = "name1";
		const char *const s1 = "name2";
		cJSON_AddItemToObject(root, body, js_body=cJSON_CreateObject());
		cJSON_AddItemToObject(js_body, list, js_list=cJSON_CreateArray());
		cJSON_AddItemToArray(js_list, cJSON_CreateString(s));
		cJSON_AddItemToArray(js_list, cJSON_CreateString(s1));
		cJSON_AddItemToObject(js_body, other, js_other=cJSON_CreateObject());
		cJSON_AddStringToObject(js_other,"name","xiaohui");
	}

#if 0
//	cJSON_AddItemToObject(root,ro,dir1=cJSON_CreateArray());
	cJSON_AddItemToObject(root,ro,dir1=cJSON_CreateObject());
	cJSON_AddNumberToObject(dir1,"key",800);
	cJSON_AddNumberToObject(dir1,"value",600);
	cJSON_AddStringToObject(dir1,"name","xiaoHu");
	cJSON_AddStringToObject(dir1,"Title","key and value");
	cJSON_AddStringToObject(dir1,"path","uploads/");
	cJSON_AddStringToObject(dir1,"flag","true");

//	cJSON_AddItemToObject(root,ro,dir2=cJSON_CreateArray());
	cJSON_AddItemToObject(root,ro,dir2=cJSON_CreateObject());
	cJSON_AddNumberToObject(dir2,"value",125);
	cJSON_AddStringToObject(dir2,"key","100");
	cJSON_AddStringToObject(dir2,"Title","value and key");
	cJSON_AddStringToObject(dir2,"name","xiaoMing");
	cJSON_AddStringToObject(dir2,"path","uploads");
	cJSON_AddStringToObject(dir2,"flag","true");
#if 1
//	cJSON_AddItemToArray(root,dir3=cJSON_CreateObject());
//	cJSON_AddItemToArray(root,ro, dir3=cJSON_CreateArray());
//	cJSON_AddItemToObject(root,ro,dir3=cJSON_CreateArray());
	cJSON_AddItemToObject(root,ro,dir3=cJSON_CreateObject());
	cJSON_AddStringToObject(dir3,"name","wang.txt");
	cJSON_AddStringToObject(dir3,"path","uploads/wang.txt");
	cJSON_AddStringToObject(dir3,"flag","false");
#endif

	dir4 = cJSON_CreateArray();
	if(!dir4) {
		DEBUG("get dir4 faild !\n");
		goto EXIT;
	}
#if 0
	cJSON_AddItemToArray(dir4, dir5 = cJSON_CreateObject());
	cJSON_AddStringToObject(dir4,"name","He.txt");
	cJSON_AddStringToObject(dir4,"path","uploads/He.txt");
	cJSON_AddStringToObject(dir4,"flag","true");

	cJSON_AddItemToArray(dir3, dir4 );
#endif
#endif
	/* copy json string to out  */
	{
//		char *s = cJSON_Print(root);
		char *s = cJSON_PrintUnformatted(root);
		if(s){
			strcpy(out, s);
			free(s);
		}
	}

//	DEBUG("%s\n",out);
	cJSON_Delete(root);

	return 0;
EXIT:
	if(root)	cJSON_Delete(root);
	return -1;
}

/*parsel a json string*/
int parsel(const char* const out)
{
	cJSON * root,*arrayItem,*item,*name,*path,*flag;
	int i = 0,size = 0;
	char *pr = NULL,*na = NULL,*pa = NULL,*fl = NULL;
	const char *temp = out;

	if(!out) {
		DEBUG("out is NULL..\n");
		goto EXIT;
	}

	root = cJSON_Parse(temp);
	if(!root) {
		DEBUG("get root faild !\n");
		goto EXIT;
	}

	size = cJSON_GetArraySize(root);
	DEBUG("size is %d\n",size);
	for(i = 0; i < size; i++) {
		arrayItem = cJSON_GetArrayItem(root,i);
		if(arrayItem) {
			pr = cJSON_Print(arrayItem);
			item = cJSON_Parse(pr);
			name = cJSON_GetObjectItem(item,"name");
			path = cJSON_GetObjectItem(item,"path");
			flag = cJSON_GetObjectItem(item,"flag");
			na = cJSON_Print(name);
			pa = cJSON_Print(path);
			fl = cJSON_Print(flag);
			DEBUG("%s\n",pr);
			DEBUG("name: %s\n",na);
			DEBUG("path: %s\n",pa);
			DEBUG("flag: %s\n\n",fl);
			free(na);
			free(pa);
			free(fl);

		}
	}

	return 0;

EXIT:
	return -1;
}


int main(int argc, char **argv)
{
	char *out = (char*)malloc(sizeof(char)*size);
	if(!out) {
		DEBUG("malloc out faild!\n");
		goto EXIT;
	}
	/* create json string */
	{
		int r = create(out);
		if(r < 0) {
			DEBUG("create json string faild..\n");
			goto EXIT;
		}else DEBUG("json string is :\n%s\n",out);
	}

#if 0
	/* parsel json string */
	{
		int r = 0;
		r = parsel(out);
		if(r < 0) {
			DEBUG("parsel faild !\n");
			goto EXIT;
		}else DEBUG("success !\n");
	}
#endif
	free(out);
	return 0;

EXIT:
	if(out) free(out);
	return -1;
}

