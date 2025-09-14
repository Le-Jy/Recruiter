CC=gcc
AR=ar
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla
OBJS=dlist_access.o dlist_init_destroy.o dlist_modify.o dlist_advanced.o main.o

all : library

bin : $(OBJS)
	$(CC) $(LDLIBS) -o $@ $^ -g

library : $(OBJS)
	$(AR) -rc libdlist.a $^

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -g

clean :
	$(RM) libdlist.a $(OBJS) bin
