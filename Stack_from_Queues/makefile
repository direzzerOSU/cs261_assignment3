CC=gcc
CFLAGS=-g -Wall -std=c99

all: prog

prog: stack_from_queue.c
	$(CC) $^ -o $@

clean:
	-rm *.o

cleanall: clean
	-rm prog