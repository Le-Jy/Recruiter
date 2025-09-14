lib_LIBRARIES = libparser.a

libparser_a_SOURCES = \
				parser.h \
				parse_input.c parse_input.h \
				parse_list.c parse_list.h \
				parse_and_or.c parse_and_or.h \
				parse_pipeline.c parse_pipeline.h \
				parse_command.c parse_command.h \
				parse_simple_command.c parse_simple_command.h \
				parse_compound_list.c parse_compound_list.h \
				parse_else.c parse_else.h \
				parse_if.c parse_if.h \
				parse_shell_command.c parse_shell_command.h \
				parse_prefix.c parse_prefix.h \
				parse_redirection.c parse_redirection.h \
				parse_element.c parse_element.h \
				parse_while.c parse_while.h \
				parse_until.c parse_until.h \
				parse_for.c parse_for.h \
				parse_funcdec.h parse_funcdec.c \
				parse_case.h parse_case.c \
				parse_case_clause.h parse_case_clause.c \
				parse_case_item.h parse_case_item.c

libparser_a_CFLAGS = -std=c99 -pedantic -Werror -Wall -Wextra -Wvla
libparser_a_CPPFLAGS = -I$(top_srcdir)/src
