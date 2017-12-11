#include "readline.h"

int
readline(int fd, void *buffer, size_t n)
{
    ssize_t read_num;
    size_t  total_read;
    char    *buf;
    char    ch;
    if (n <= 0 || buffer == NULL) {
        errno = EINVAL;
        return -1;
    }
    buf = buffer;
    for(;;) {
        read_num = read(fd,&ch,1);
        /* 读取失败  */
        if (read_num == -1) {
            /* 调用中断 */
            if (errno == EINTR) 
                continue;
            else
                return -1;
        /* 读取结束 */
        } else if(read_num == 0) {
            if (total_read == 0)
                return 0;
            else
                break;
        /* 读取完指定的n字节 */
        }else {
            if (total_read < n-1) {
                total_read++;
                *buf++ = ch;
            }
            if (ch == '\n') {
                break;
            }
        }
    }
    *buf = '\0';
    return total_read;
}


