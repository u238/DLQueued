CC=gcc
CFLAGS="-Wall"
LIBS="-lcurl -lpthread"

debug:clean
	$(CC) $(CFLAGS) -O2 -g -o ../bin/dlqueued -lcurl -lpthread log.c dlpart.c dlqueued.c
stable:clean
	$(CC) $(CFLAGS) -o ../bin/dlqueued -lcurl -lpthread log.c dlpart.c dlqueued.c
clean:
	rm -vfr *~ dlqueued
