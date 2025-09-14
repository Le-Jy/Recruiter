CC=gcc
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla

OBJS=bst.o bst_static.o main.o

all : bin

bin : $(OBJS)
	$(CC) -o $@ $^

clean :
	$(RM) $(OBJS) bin
