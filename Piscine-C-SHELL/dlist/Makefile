CC=gcc
AR=ar
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla

OBJS=dlist_access.o dlist_init_destroy.o dlist_modify.o

all : library

bin : $(OBJS)
	$(CC) $(LDLIBS) -o $@ $^

library : $(OBJS)
	$(AR) -rc libdlist.a $^

%.o : %.c
	$(CC) $(CFLAGS) -c $^

clean :
	$(RM) libdlist.a $(OBJS) bin
