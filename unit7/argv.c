/*打印命令行参数*/
#include "apue.h"

int
main(int argc, char const *argv[])
{
	int i;
	if (argc != 2)
		err_msg("缺少命令行参数");
	for (i=1;i<argc;i++) {
		puts(argv[i]);
	}
	return 0;
}