lib_LIBRARIES = libutils.a

libutils_a_SOURCES = \
					 hash_map/hash.c hash_map/hash_map.c hash_map/hash_map.h \
					 list/list.h list/list.c \
					 string_arrays/string_arrays.c string_arrays/string_arrays.h \
					 itoa/itoa.c itoa/itoa.h \
					 count_children/count_children.c count_children/count_children.h \
					 hash_map_funcdec/hash_funcdec.c hash_map_funcdec/hash_map_funcdec.c hash_map_funcdec/hash_map_funcdec.h


libutils_a_CFLAGS = -std=c99 -pedantic -Werror -Wall -Wextra -Wvla
libutils_a_CPPFLAGS = -I$(top_srcdir)/src
