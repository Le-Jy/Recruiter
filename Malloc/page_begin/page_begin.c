#include "page_begin.h"

void *page_begin(void *ptr, size_t page_size)
{
    size_t sizet_ptr = (size_t)ptr;
    size_t start = sizet_ptr & ~(page_size - 1);
    char *res = ptr;
    return res - (sizet_ptr - start);
}
