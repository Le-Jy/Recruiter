lib_LIBRARIES = libexpansion.a

libexpansion_a_SOURCES = \
					expand_word.c expand_word.h \
					expand_quote.c expand_quote.h \
					expand_double_quotes.c expand_double_quotes.h \
					expand_backslash.c expand_backslash.h \
					expand_variable.c expand_variable.h \
					expansion.c expansion.h \
					variables.c variables.h \
					quote_removal.c quote_removal.h \
					field_splitting.c field_splitting.h


libexpansion_a_CFLAGS = -std=c99 -pedantic -Werror -Wall -Wextra -Wvla
libexpansion_a_CPPFLAGS = -I$(top_srcdir)/src
