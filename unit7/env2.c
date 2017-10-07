/*
#include <stdlib.h>
char *getenv(const char *name);
成功：返回与name相关的value指针 失败：返回NULL

int putenv(const char *name); 设置环境变量name=value形式,如果name存在,则删除其定义
成功:返回0 出错:返回非0

int setenv(const char *name,const char *value, int rewrite);
成功：返回0 失败: 返回-1
rewrite为0,则不覆盖现有的定义,非零则覆盖

int unsetenv(const char *name);
成功: 返回0 失败：返回-1
*/
#include "apue.h"

extern char **environ;

int
main(int argc, char const *argv[])
{
	char *value;
	puts("call getenv(PATH)");
	if ((value = getenv("PATH")) == NULL)
		err_sys("getenv");
	puts(value);

	puts("call putenv(PATH=aaa)");
	if (putenv("PATH=aaa") != 0)
		err_sys("putenv");
	puts(getenv("PATH"));

	puts("call setenv(PATH,bbb,1)");
	if (setenv("PATH","bbb",1) != 0)
		err_sys("setenv");
	puts(getenv("PATH"));

	puts("call unsetenv(PATH)");
	if (unsetenv("PATH") != 0)
		err_sys("unsetenv");

	if ((value =getenv("PATH")) == NULL)
		puts("unknown PATH");
	return 0;
}