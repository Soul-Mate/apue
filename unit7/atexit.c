/*
atexit注册exit函数,调用顺序FILO
int atexit(void (*func)(void))
成功返回0,出错返回非0
*/
#include "apue.h"

void my_exit1();
void my_exit2();

int 
main(int argc, char const *argv[])
{
	if (atexit(my_exit1) != 0)
		err_sys("my_exit1");
	if (atexit(my_exit2) != 0)
		err_sys("my_exit2");
	puts("main done");
	return 0;
}

void my_exit1()
{
	puts("fist exit");
}

void my_exit2()
{
	puts("second exit");
}