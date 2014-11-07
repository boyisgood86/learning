#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ym_json.h"


enum err_code
{
	ym_ok = 1,
	ym_err = -1,
};

int ym_json_creat(js_root_t *js, char * js_string);                                                                   
int ym_json_parsel(js_root_t *js, const char * const js_string);


int ym_json_creat(js_root_t *js, char * js_string)
{
	if(!js || !js_string) {
		printf("%s,%d: js or string is NULL!\n",__func__,__LINE__)	;
		goto EXIT;
	}

	js->root = cJSON_CreateObject();
	if(!js->root) {
		printf("%s,%d: get root faild !\n",__func__,__LINE__);
		goto EXIT;
	}

	/*body*/
	if(js->body) {
		printf("%d: create body!\n",__LINE__);
		cJSON_AddItemToObject(js->root,"body", js->ym_body.body = cJSON_CreateObject());
		/*list*/
		int i = 0;
		if(js->ym_body.list){
			cJSON_AddItemToObject(js->ym_body.body, "list", 
					js->ym_body.ym_list.list = cJSON_CreateArray());
			if(js->ym_body.ym_list.flag == YM_ARRAY){
			/*array*/
				for(i = 0; i < js->ym_body.ym_list.size; i++)	
					cJSON_AddItemToArray(js->ym_body.ym_list.list , cJSON_CreateString("Hello world !"));
				//TODO...
			}else if(js->ym_body.ym_list.flag == YM_OBJECT){
			/*device*/
				for(i = 0; i < js->ym_body.ym_list.size; i++) {
					cJSON_AddItemToArray(js->ym_body.ym_list.list , 
							( js->ym_body.ym_list.ym_dev+i )->dev = cJSON_CreateObject());
					cJSON_AddStringToObject(( js->ym_body.ym_list.ym_dev+i )->dev, "device_mac",
							( js->ym_body.ym_list.ym_dev+i )->device_mac);
					cJSON_AddNumberToObject(( js->ym_body.ym_list.ym_dev+i )->dev, "devcice_progress", 
							( js->ym_body.ym_list.ym_dev+i )->devcice_progress);
				}
			}else
			;	/*TODO...*/

		}
		/*other*/
		if(js->ym_body.other) {
			cJSON_AddItemToObject(js->ym_body.body, "other", 
					js->ym_body.ym_other.other = cJSON_CreateObject());	
			cJSON_AddNumberToObject(js->ym_body.ym_other.other ,"isAuthority",js->ym_body.ym_other.isAuthority);
		}
		/*user*/
		if(js->ym_body.user) {
			cJSON_AddItemToObject(js->ym_body.body, "user", 
				js->ym_body.ym_user.user = cJSON_CreateObject());	
			cJSON_AddStringToObject(js->ym_body.ym_user.user,"name",js->ym_body.ym_user.name);
			cJSON_AddStringToObject(js->ym_body.ym_user.user,"password",js->ym_body.ym_user.passwd); 
		}
	}
	/* head */
	if(js->head) {
		printf("%d: create head!\n",__LINE__);
		cJSON_AddItemToObject(js->root,"head", js->ym_head.head = cJSON_CreateObject());
		cJSON_AddStringToObject(js->ym_head.head,"message",js->ym_head.message);
		cJSON_AddNumberToObject(js->ym_head.head,"method",js->ym_head.method);
		cJSON_AddStringToObject(js->ym_head.head,"mobileid",js->ym_head.mobileid);
		cJSON_AddNumberToObject(js->ym_head.head,"status",js->ym_head.method);
		cJSON_AddStringToObject(js->ym_head.head,"boxid",js->ym_head.boxid);
	}
	{
		char *s = cJSON_PrintUnformatted(js->root);
		if(s) {
			strcpy(js_string, s);
			free(s);
		}
	}

	if(js->root)
		cJSON_Delete(js->root);
	return ym_ok;
EXIT:
	if(js->root)
		cJSON_Delete(js->root);
	return ym_err;
}


int ym_json_parsel(js_root_t *js, const char * const js_string)
{
	if(!js || !js_string) {
		printf("%s,%d: js or js_string is NULL!\n",__func__,__LINE__);
		goto EXIT;
	}
 /*root*/
	js->root = cJSON_Parse(js_string);
	if(!js->root) {
		printf("%s,%d: get root faild !\n",__func__,__LINE__);
	}
/*get body*/	
	if(js->body) {
		js->ym_body.body = cJSON_GetObjectItem(js->root, "body");
		if(js->ym_body.body) {
			/*get list*/
			if(js->ym_body.list) {
				int size = 0;
				int i = 0;
				char *p = NULL;
				cJSON *item, *it, *dev_mac, *dev_pro;

				js->ym_body.ym_list.list = cJSON_GetObjectItem(js->ym_body.body, "list");
				if(!js->ym_body.ym_list.list) {
					size = 0;
				}else{
					 size = cJSON_GetArraySize( js->ym_body.ym_list.list);
				}
				if(js->ym_body.ym_list.flag == YM_ARRAY && size > 0) {
					//TODO...	
				}else if(js->ym_body.ym_list.flag == YM_OBJECT && size > 0){
					/*malloc space*/
					js->ym_body.ym_list.ym_dev = (js_dev_t*)malloc(size);
					if(!js->ym_body.ym_list.ym_dev){ 
						size = 0;
						printf("%s,%d: malloc faild !\n",__func__,__LINE__);
					}
					memset(js->ym_body.ym_list.ym_dev, 0, size);

					for(i = 0; i < size; i++){
						item = cJSON_GetArrayItem(js->ym_body.ym_list.list, i);
						if(item) {
							p =  cJSON_PrintUnformatted(item);	
							it = cJSON_Parse(p);
							if(!it)
								continue ;
							dev_mac = cJSON_GetObjectItem(it, "device_mac");
							memcpy((js->ym_body.ym_list.ym_dev+i)->device_mac, dev_mac->valuestring, 24);
							dev_pro = cJSON_GetObjectItem(it, "dev_progress");
							(js->ym_body.ym_list.ym_dev+i)->devcice_progress = dev_pro->valueint;
						}
					}
				}else
					; //TODO...
				js->ym_body.ym_list.size = size;
//				if(it){ 
//					cJSON_Delete(it);
//				}
			} /*end of list*/

			/*get user*/
			if(js->ym_body.user) {
				js->ym_body.ym_user.user = cJSON_GetObjectItem(js->ym_body.body, "user");
				if(js->ym_body.ym_user.user) {
					cJSON *name , *passwd;
					/*get name*/
					name = cJSON_GetObjectItem(js->ym_body.ym_user.user, "name");
					if(name) {
						strcpy(js->ym_body.ym_user.name, name->valuestring);
					}
					/*get passwd*/
					passwd = cJSON_GetObjectItem(js->ym_body.ym_user.user, "password");
					if(passwd) {
						strcpy(js->ym_body.ym_user.passwd, passwd->valuestring);
					}
				}
			}
			/*get other*/
			if(js->ym_body.other){
				js->ym_body.ym_other.other = cJSON_GetObjectItem(js->ym_body.body, "other");
				if(js->ym_body.ym_other.other) {
					cJSON *other;
					other =  cJSON_GetObjectItem(js->ym_body.ym_other.other, "isAuthority");
					if(other) {
						js->ym_body.ym_other.isAuthority = other->valueint;
					}
				}
			} /*end of other*/
		}
	}
/*get head*/
	if(js->head){
		js->ym_head.head = cJSON_GetObjectItem(js->root, "head");
		if(js->ym_head.head) {
			cJSON *method, *status, *mobileid,*boxid, *message;
			/*get method*/
			method = cJSON_GetObjectItem(js->ym_head.head, "method");
			if(method) {
				js->ym_head.method = method->valueint;
			}
			/*get status*/
			status = cJSON_GetObjectItem(js->ym_head.head, "status");
			if(status) {
				js->ym_head.status = status->valueint;
			}
			
			/*get mobileid*/
			mobileid = cJSON_GetObjectItem(js->ym_head.head, "mobileid");
			if(mobileid) {
				strcpy(js->ym_head.mobileid, mobileid->valuestring);
			}

			/*get  boxid */
			boxid = cJSON_GetObjectItem(js->ym_head.head, "boxid");
			if(boxid) {
				strcpy(js->ym_head.boxid, boxid->valuestring);
			}

			/*get message */
			message = cJSON_GetObjectItem(js->ym_head.head, "message");
			if(message) {
				memcpy(js->ym_head.message, message->valuestring, 24);
			}
		}
	
	} /*end of head*/

	if(js->root)
		cJSON_Delete(js->root);
	return ym_ok;
EXIT:
	if(js->root)
		cJSON_Delete(js->root);
	return ym_err;
}

