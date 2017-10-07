/*
打印环境变量
char **environ保存当前程序环境变量
*/
#include "apue.h"

extern char **environ;

int
main(int argc, char const *argv[])
{
	while(*environ!= NULL) {
		puts(*environ);
		environ++;
	}
	return 0;
}