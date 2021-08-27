CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -ggdb3 -std=gnu90
UTILS = utils

.PHONY: clean

strace_5: strace_5.o $(UTILS).o strace.h syscalls.h
	$(CC) $(CFLAGS) -o $@  $^

strace_4: strace_4.o $(UTILS).o strace.h syscalls.h
	$(CC) $(CFLAGS) -o $@  $^

strace_3: strace_3.o strace.h syscalls.h
	$(CC) $(CFLAGS) -o $@  $^

strace_2: strace_2.o strace.h syscalls.h
	$(CC) $(CFLAGS) -o $@  $^

strace_1: strace_1.o strace.h syscalls.h
	$(CC) $(CFLAGS) -o $@  $^

strace_0: strace_0.o strace.h syscalls.h
	$(CC) $(CFLAGS) -o $@  $^

clean:
	rm *.o strace_0 strace_1 strace_2 strace_3 strace_4 strace_5
