CC=gcc
AR=ar
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla

OBJS = fifo_access.o fifo_setup_destroy.o

all : library

library : $(OBJS)
	$(AR) -rc libfifo.a $^

bin : $(OBJS)
	$(CC)  -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $^

clean :
	$(RM) libfifo.a $(OBJS)
