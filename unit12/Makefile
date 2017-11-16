
ROOT=..
#PLATFORM=$(shell $(ROOT)/systype.sh)
PLATFORM=linux
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	pthread_create printids pthread_join pexit pcancel pcleanup pnosync pmutex1 pmutex2 deadlock1 producer_consumer
all:	$(PROGS)

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -lpthread -lrt -g -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o
	rm -f *.txt
include $(ROOT)/Make.libapue.inc
