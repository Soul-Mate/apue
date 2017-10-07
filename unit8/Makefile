ROOT=..
#PLATFORM=$(shell $(ROOT)/systype.sh)
PLATFORM=linux
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	fork wait racecondition exec echo system
all:	$(PROGS)

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o
	rm -f *.txt
include $(ROOT)/Make.libapue.inc
