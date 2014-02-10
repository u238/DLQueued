CC=gcc
CFLAGS="-Wall"

debug:clean
	$(CC) $(CFLAGS) -g -o dlqueued main.c
stable:clean
	$(CC) $(CFLAGS) -o dlqueued main.c
clean:
	rm -vfr *~ dlqueued
