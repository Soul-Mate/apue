ROOT=..
#PLATFORM=$(shell $(ROOT)/systype.sh)
PLATFORM=linux
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	atexit argv env env2 jmp getuid getgid
all:	$(PROGS)

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o
	rm -f *.txt
include $(ROOT)/Make.libapue.inc
