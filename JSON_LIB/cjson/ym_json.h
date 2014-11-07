#ifndef __YM_JSON_H_
#define __YM_JSON_H_

#include "cJSON.h"
/*
 * statu  device value
 * mac   device address
 * */

typedef struct js_device
{
	char devcice_progress;
	char device_mac[25];

	cJSON * dev;
}js_dev_t;


typedef struct js_user_list
{
	char name[16];
}js_user_ls_t;

/* Array List */

#define YM_ARRAY	(1)
#define YM_OBJECT	(2)

typedef struct js_list
{
//whitelist	
	char flag ;    /*set YM_ARRY or YM_OBJECT*/
	char size;	/*array or object count  about list item*/

	js_dev_t *ym_dev;
	js_user_ls_t *ym_user;

	cJSON *list;
}js_ls_t;

/*json string other*/
typedef struct js_other
{
	char isAuthority;

	cJSON *other;
}js_other_t;

/* json string user */
typedef struct js_user
{
	char name[16];
	char passwd[16];
	char new_passwd[16];

	cJSON *user;
}js_user_t;

/* json string head*/
typedef struct js_head
{
	char status;
	char mobileid[18];
	char boxid[18];
	char message[25];
	int method;

	cJSON *head;
}js_head_t;


/* body */
typedef struct js_body
{
	char list; /*if you care the list item in json string , set 1, or  zero it*/
	char user; /*if you care the user item in json string, set 1, or zero it*/
	char other; /*if you care the other item in json string , set 1, or zero it*/

	js_ls_t		ym_list;
	js_other_t	ym_other;
	js_user_t	ym_user;

	cJSON *body;
}js_body_t;

/* root */
typedef struct js_root
{
	char body; /*if you care the body item in json string, set 1, or zero it*/
	char head; /*if you care the head item in json string, set 1, or zero it*/

	js_head_t ym_head;
	js_body_t ym_body;

	cJSON *root;
}js_root_t;

/* creat a json string, and put it into js_string*/
int ym_json_creat(js_root_t *js, char * js_string);
/*parsel a json string which from js_string, and put the answer into the struct js_root_t*/
int ym_json_parsel(js_root_t *js, const char * const js_string);


#endif /* __YM_JSON_H_*/

