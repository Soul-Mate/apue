/*
off_t lseek(int fd,off_t offset,mode_t mode);
设置文件的偏移量 成功返回当前文件偏移量,失败返回-1
mode有三种模式
SEEK_SET 从文件开始处便宜offset字节
SEEK_END 从未见末尾 可负
SEEK_CUR 从当前位置 可负
*/
#include "apue.h"
int
main(int argc, char const *argv[])
{
	if (lseek(STDIN_FILENO,0,SEEK_CUR) == -1)
		err_msg("cannot lseek");
	printf("STDIN_FILENO lseek ok\n");
	return 0;
}