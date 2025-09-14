CC = gcc
AR = ar
CFLAGS = -std=c99 -pedantic -Werror -Wall -Wextra -Wvla

OBJS = src/lbs_fopen.o src/lbs_fflush.o

OBJS_TEST = stdout_buffering_test.o stdin_buffering_test.o

all : library

library : $(OBJS)
	ar -rc libstream.a $^

stdout_buffering_test : stdout_buffering_test.o
	$(CC) -o $@ $^

stdin_buffering_test : stdin_buffering_test.o
	$(CC) -o $@ $^

clean :
	$(RM) $(OBJS) $(OBJS_TEST) stdin_buffering_test stdout_buffering_test
	$(RM) libstream.a
