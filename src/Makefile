CC=gcc
CFLAGS="-Wall"

debug:clean
	$(CC) $(CFLAGS) -g -o ../bin/dlqueued -lpthread -lcurl dlqueued.c
stable:clean
	$(CC) $(CFLAGS) -o ../bin/dlqueued -lpthread -lcurl dlqueued.c
clean:
	rm -vfr *~ dlqueued
