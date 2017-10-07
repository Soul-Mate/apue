#include "apue.h"


int
main(int argc, char const *argv[])
{
	extern char **environ;
	char **ptr;
	if (argc < 2)
		exit(0);

	int i;
	/* print args */
	for (i=0;i<argc;i++) {
		puts(argv[i]);
	}
	/* print environ */
	for (ptr = environ; *ptr!=NULL;ptr++) {
		puts(*ptr);
	}
	return 0;
}