/*
#include <setjmp.h>
int setjmp(jmp_buf env);
直接调用返回0;从longjmp返回非0

jmp_buf是一个特殊类型,用来存放调用longjmp后程序恢复栈状态的所有信息。

void longjmp(jmp_buf env, int val);

longjmp第一个参数就是调用setjmp时的env,第二个参数是非0的val,它将成为从setjmp处返回的值

*/

#include "apue.h"
#include <setjmp.h>

jmp_buf jmpbuffer;

static int globalval;			/* 全局变量 */

static void f1(int autoval,int registerval,int volatileval,int staticval);
static void f2();

int
main(int argc, char const *argv[])
{

	int autoval; 				/* 自动变量 */
	register int registerval;	/* 寄存器变量 */
	volatile int volatileval;	/* 易失变量 */
	static int staticval;		/* 静态变量 */


	globalval = 1; autoval = 2; registerval = 3; volatileval = 4; staticval = 5;

	if (setjmp(jmpbuffer) != 0) {
		printf("after longjmp:\n");
		printf("global = %d, autoval = %d, register = %d, volatile = %d, static = %d\n",globalval,autoval,registerval,volatileval,staticval);
		exit(0);
	}
	globalval = 95; autoval = 96; registerval = 97; volatileval = 98; staticval = 99;
	f1(autoval,registerval,volatileval,staticval);
	return 0;
}
static void 
f1(int autoval,int registerval,int volatileval,int staticval)
{
	puts("f1:");
	printf("global = %d, autoval = %d, register = %d, volatile = %d, static = %d\n",globalval,autoval,registerval,volatileval,staticval);
	f2();
}

static void
f2()
{
	longjmp(jmpbuffer,1);
}