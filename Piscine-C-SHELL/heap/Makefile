CC=gcc
AR=ar
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla

OBJS = create.o add.o del.o pop.o print.o

all : library

library : $(OBJS)
	$(AR) -rc libheap.a $^

bin : $(OBJS)
	$(CC)  -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $^

clean :
	$(RM) libheap.a $(OBJS)
