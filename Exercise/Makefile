# the compiler: gcc for C program, define as g++ for C++
CC = gcc
CFLAGS  = -g -Wall

all: copy_low copy_high copy_pipe

copy_low: copy_low.c
	$(CC) $(CFLAGS) -o copy_low copy_low.c

copy_high: copy_high.c
	$(CC) $(CFLAGS) -o copy_high copy_high.c

copy_pipe: copy_pipe.c
	$(CC) $(CFLAGS) -o copy_pipe copy_pipe.c

clean:
	$(RM) copy_low copy_high copy_pipe
