bin_PROGRAMS = 42sh
42sh_SOURCES = 42sh.c \
	main_loop.c main_loop.h

42sh_CFLAGS = -std=c99 -pedantic -Werror -Wall -Wextra -Wvla
42sh_CPPFLAGS = -I%D%

42sh_LDADD = \
	parser/libparser.a \
	lexer/liblexer.a \
	ast/libast.a \
	io/libio.a \
	options/liboptions.a \
	execution/libexecution.a \
	expansion/libexpansion.a \
	utils/libutils.a


SUBDIRS = \
	parser \
	lexer \
	ast \
	io \
	options \
	execution \
	expansion \
	utils
