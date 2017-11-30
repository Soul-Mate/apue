#include <stdio.h>
#include <unistd.h>
#include <perrno.h>

static int pipefd1[2],pipefd2[2];

void
TELL_WAIT()
{
    if (pipe(pipefd1) < 0 || pipe(pipefd2) < 0) {
        printf("pipe error");
        exit(0);
    }
}

void
TELL_CHILD()
{
    if (write(pipefd[1],'c',1) ! = 1) {
        printf("write error");
        exit(0);
    }
}

void
WAIT_PARENT()
{
    if (close(pipefd[0]) < 0) {
        printf("close error");
        exit(0);
    }
    if (read(pipefd[1]))
}
