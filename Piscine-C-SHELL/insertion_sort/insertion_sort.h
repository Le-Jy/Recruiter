#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <stddef.h>

typedef int (*f_cmp)(const void *f1, const void *f2);

void insertion_sort(void **array, f_cmp comp);

#endif /* ! INSERTION_SORT_H */
