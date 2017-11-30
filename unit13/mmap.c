#include "apue.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#ifndef COPYINCR
#define COPYINCR (1024 * 1024 * 1024)
#endif

/* 创建输入流的共享内存  */
void *create_in_mmap(int fdin, size_t copy_size, off_t file_size);

/* 创建输出流的共享内存  */
void *create_out_mmap(int fdout, size_t copy_size, off_t file_size);

/* 打开输入文件 */
int open_in_file(const char *file);

/* 打开或创建输出文件 */
int open_out_file(const char *file);


int 
main(int argc, const char *argv[])
{
    if (argc != 3) {
        printf("usage: %s <fromfile> <tofile>",argv[0]);
        exit(0);
    }
    if (strcmp(argv[0],"-h") == 0 || strcmp(argv[1],"help") == 0) {
        printf("usage: %s <fromfile> <tofile>",argv[0]);
        exit(0);
    }
    int         fdin,fdout;
    off_t       file_size = 0;
    size_t      copy_size;
    void        *src,*dst;
    struct stat sbuf;
    fdin = open_in_file(argv[1]);
    fdout = open_out_file(argv[2]);
    if (fdout < 0)
        err_sys("open failed");
    if (fstat(fdin,&sbuf) < 0) 
        err_sys("fstat error");
    if (ftruncate(fdout,sbuf.st_size) < 0)
        err_sys("ftruncate error");
    while(file_size < sbuf.st_size) {
        if (sbuf.st_size - file_size > COPYINCR ) 
            copy_size =  COPYINCR;
        else 
            copy_size = sbuf.st_size - file_size;
        src = create_in_mmap(fdin,copy_size,file_size);
        dst = create_out_mmap(fdout,copy_size,file_size);
        memcpy(dst,src,copy_size);
        munmap(src,copy_size);
        munmap(dst,copy_size);
        file_size += copy_size;
    }
    return 0;
}

void *
create_in_mmap(int fdin, size_t copy_size, off_t file_size)
{
    void *src;
    if ((src = mmap(0,copy_size,PROT_READ,MAP_SHARED,fdin,file_size))
            == MAP_FAILED)
        err_sys("create mmap fdin failed");
    return src;
}

void *
create_out_mmap(int fdout, size_t copy_size, off_t file_size)
{
    void *dst;
    if ((dst = mmap(0, copy_size, PROT_READ|PROT_WRITE, MAP_SHARED, fdout, file_size))
            == MAP_FAILED)
        err_sys("create mmap fdout failed");
    return dst;
}

int 
open_in_file(const char *file)
{
    int fd = open(file,O_RDONLY);
    if (fd < 0)
        err_sys("open failed");
    return fd;
}

int
open_out_file(const char *file)
{
    int exist_file;
    if ((exist_file = access(file,F_OK)) == 0) 
        if (unlink(file) < 0)
            err_sys("unlink failed");
    int fd = open(file,O_RDWR|O_CREAT|O_TRUNC,FILE_MODE);
    if (fd < 0)
        err_sys("open failed");
    return fd;
}
