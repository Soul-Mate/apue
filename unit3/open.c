/* int open(const char *path.int flag,...mode_t mode);
 打开一个文件,最后一个参数只有在设置了相应的flag状态才使用到
 成功返回文件描述符 失败返回-1 */

#include "apue.h"
#include <fcntl.h>
int 
main(int argc, char const *argv[])
{
	if ( argc!=2 )
		err_exit(1,"path");
	/*文件描述符*/
	int fd;
	/*读-写方式打开一个文件,如果不存在,则创建*/
	fd = open(argv[1],O_RDWR|O_CREAT|O_EXCL|O_TRUNC,0644);
	
	if (fd < 0)
		err_sys("open error");
	else
		printf("fd [%d] open\n",fd);
	return 0;
}