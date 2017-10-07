 #include "apue.h"

int main(int argc, char const *argv[])
{
	
	gid_t gid1,gid2;
	gid1 = getgid();
	gid2 = getegid();
	printf("real group id:%d\n", gid1);
	printf("effective group id %d\n",gid2);
	return 0;
}