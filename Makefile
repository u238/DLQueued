CC=gcc
CFLAGS="-Wall"

debug:clean
	$(CC) $(CFLAGS) -g -o dlqueued -lpthread -lcurl main.c
stable:clean
	$(CC) $(CFLAGS) -o dlqueued -lpthread -lcurl main.c
clean:
	rm -vfr *~ dlqueued
