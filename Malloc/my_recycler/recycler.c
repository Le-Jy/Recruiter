#include "recycler.h"

#include <stdlib.h>

struct recycler *recycler_create(size_t block_size, size_t total_size)
{
    if (block_size == 0 || total_size == 0 || block_size % 8 != 0
        || total_size % block_size != 0)
        return NULL;
    struct recycler *res = malloc(sizeof(struct recycler));
    if (!res)
        return NULL;
    res->capacity = total_size / block_size;
    res->block_size = block_size;
    res->chunk = malloc(total_size);
    if (!res->chunk)
    {
        free(res);
        return NULL;
    }
    struct free_list *current = res->chunk;
    char *ch = res->chunk;
    res->free = res->chunk;
    for (size_t i = 1; i < res->capacity; i++)
    {
        void *tmp = ch + i * res->block_size;
        current->next = tmp;
        current = current->next;
    }
    return res;
}

void recycler_destroy(struct recycler *r)
{
    if (r)
    {
        free(r->chunk);
        free(r);
    }
}

void *recycler_allocate(struct recycler *r)
{
    if (r)
    {
        if (r->free)
        {
            void *res = r->free;
            struct free_list *tmp = r->free;
            r->free = tmp->next;
            return res;
        }
    }
    return NULL;
}

void recycler_free(struct recycler *r, void *block)
{
    if (r && block)
    {
        struct free_list *current = r->free;
        r->free = block;
        current->next = current;
    }
}
