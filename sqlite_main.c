#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#define SIZE	(256)

#define	_DEBUG
#ifdef _DEBUG
#define DEBUG(fmt, arg...)	do{printf(fmt, ##arg);}while(0)
#else
#define DEBUG(fmt, arg...)	do{}while(0)
#endif


int callback(void *arg, int nr, char **values, char **names)
{
	int i = 0;
	FILE *fp = (FILE*)arg;

	char str[SIZE];
	DEBUG("%s, %d: Now in here..\n",__func__,__LINE__);
	for(i = 0; i < nr; i++) {
		memset(str, 0, SIZE);
		sprintf(str, "%s", values[i]);
		fwrite(str, sizeof(char), sizeof(str), fp);
	}

	memset(str, 0, SIZE);
	fwrite("\n",sizeof(char),2, fp);
	return 0;
}


int main(int argc, char **argv)
{
	sqlite3 *db; 
	int result;
//	FILE * fp = NULL;
	char **dbResult;
	char *errmsg = NULL;
	int nRow, nColumn;
	int i, j, index;

	if(argc != 3) {
		DEBUG("Usage: a.out \"db name\" \"command string\"\n");
		return -1;
	}

	/* open or create */
	result = sqlite3_open(argv[1], &db);
	if(result != SQLITE_OK) {
		DEBUG("open or create faild : %s \n",sqlite3_errmsg(db));
		return -1;
	}else {
		DEBUG("open success !\n");
	}
	/* create a table */
	result = sqlite3_exec(db, "create table tb(ID integer primary key autoincrement, name nvarchar(32))", NULL, NULL, NULL);
	if(result != SQLITE_OK) {
		DEBUG("creat table faild : %d, %s \n",result, sqlite3_errmsg(db));
		return -1;
	}else {
		DEBUG("create success !\n");
	}
	/*inseret*/
	result = sqlite3_exec(db, "insert into tb(name) values('go')", 0,0,&errmsg);
	if(result != SQLITE_OK) {
		DEBUG("%s, %d: insert faild: %s\n",__func__,__LINE__,errmsg);
		return -1;
	}
	/*select*/
	result = sqlite3_get_table(db,"select * from tb", &dbResult, &nRow, &nColumn, &errmsg );
	if(result == SQLITE_OK) {
		DEBUG("%s, %d: select success !\n",__func__,__LINE__);
		index = nColumn;
		for(i = 0; i < nRow; i++) {
			DEBUG("The %d index\n",i);
			for (j = 0; j < nColumn; j++) {
				DEBUG("字段名: %s > 字段值 %s \n",dbResult[j], dbResult [index]);
				++index;
			}
			DEBUG("------\n");
		}
	}
	sqlite3_free_table( dbResult );
	sqlite3_close( db );
#if 0
	fp = fopen(argv[2], "w+") ;
	if( !fp) {
		DEBUG("open file %s faild !\n",argv[2]);
		return -1;
	}
	/* select */
	result = sqlite3_exec(db, "select * from tb", callback, fp, NULL);
	if(result != SQLITE_OK) {
		DEBUG("select database faild: %s..\n",sqlite3_errmsg(db));
		return -1;
	}else {
		DEBUG("select success !\n");
	}

	/* close */
	sqlite3_close(db);
	fclose(fp);
#endif
	return 0;
}

