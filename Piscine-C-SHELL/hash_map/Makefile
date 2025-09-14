CC = gcc
CFLAGS = -std=c99 -pedantic -Werror -Wall -Wextra -Wvla -fsanitize=address -g
LDLIBS = -fsanitize=address

OBJS = hash_map.o hash.o main.o
all : bin

bin : $(OBJS)
	$(CC) $(LDLIBS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $^

clean :
	$(RM) $(OBJS) bin
