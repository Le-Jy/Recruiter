CC=gcc
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla

SRC=vector.c
SRCD=main.c
OBJS=vector.o
OBJSD=main.o

library : $(OBJS)
	ar -rcs libvector.a $^

bin : $(OBJS) $(OBJSD)
	$(CC) -o vector $^

OBJS : $(SRC)
	$(CC) $(CFLAGS) -c $^

OBJSD : $(SRCD)
	$(CC) $(CFLAGS) -c $^

all : library

.PHONY : all clean

clean :
	$(RM) vector $(OBJS) $(OBJSD) libvector.a










