#include "apue.h"

int
main(int argc, char const *argv[])
{
	uid_t uid;
	uid = getuid();
	printf("user ID: %d\n", uid);
	return 0;
}