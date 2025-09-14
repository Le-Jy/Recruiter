CC=gcc
CFLAGS=-Wall -Wextra -Werror -Wvla -pedantic -std=c99 -g3 -O0

OBJS=my_strstr.o main.o

all: bin

bin : $(OBJS)
	$(CC) $(OBJS) -o bin


clean:
	rm bin
	rm *.o
