CC = gcc
AR = ar
CFLAGS = -std=c99 -Werror -Wall -Wextra -Wvla
LDLIBS = -lcriterion

OBJS = is_something.o count.o print.o
OBJD = test.o

all : library

library : $(OBJS)
	$(AR) -rcs libbinary_tree.a $^

test : $(OBJS) $(OBJD)
	$(CC) $(LDLIBS) -o $@ $^

clean :
	$(RM) $(OBJD) $(OBJS) test libbinary_tree.a
