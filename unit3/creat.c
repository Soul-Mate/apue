/* int creat(const char *path,mode_t mode);
调用成功返回文件描述符,失败返回-1
create函数创建一个文件,值得注意的是,creat以写的方式打开文件
如果使用create创建一个文件想获得读的权限 可以 create->close->open
*/

#include "apue.h"
#include <fcntl.h>

int
main(int argc, char const *argv[])
{
	int fd;
	
	if (argc !=2 )
		err_exit(1,"path");
	
	fd = creat(argv[1],0644);
	if (fd < 0)
		err_sys("open");
	else
		printf("create %s fd [%d]\n",argv[1],fd);
	return 0;
}