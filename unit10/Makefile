
ROOT=..
#PLATFORM=$(shell $(ROOT)/systype.sh)
PLATFORM=linux
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	signal kill raise sleep1 sleep2 alarm_read1 alarm_read2 sigaction_signal sigjmp sigipc
all:	$(PROGS)

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o
	rm -f *.txt
include $(ROOT)/Make.libapue.inc
