#include <stddef.h>
#include <string.h>

#include "allocator.h"

struct blk_meta *g_list = NULL;

static void check_address(void *ptr)
{
    int found = 0;
    struct blk_meta *buckets = g_list;
    while (!found && buckets)
    {
        char *data = buckets->chunk;
        char *p = ptr;

        if (p >= data && p <= data + (buckets->size - buckets->blk_size))
        {
            buckets = block_free(buckets, ptr);
            if (buckets && !buckets->previous)
                g_list = buckets;
            else if (!buckets)
                g_list = NULL;
            found = 1;
        }
        if (!found)
            buckets = buckets->next;
    }
}

static size_t round_up(size_t size)
{
    size_t block_size = 1;
    while (block_size <= 8 || size > block_size)
        block_size = block_size << 1;
    return block_size;
}

__attribute__((visibility("default"))) void *malloc(size_t size)
{
    if (size == 0)
        return NULL;
    size = round_up(size);
    if (!g_list)
    {
        g_list = blka_alloc(NULL, size);
        return block_allocate(g_list);
    }
    else
    {
        struct blk_meta *tmp = g_list;
        while (tmp)
        {
            if (tmp->blk_size == size && tmp->free)
            {
                return block_allocate(tmp);
            }
            tmp = tmp->next;
        }
        g_list = blka_alloc(g_list, size);
        return block_allocate(g_list);
    }
    return NULL;
}

__attribute__((visibility("default"))) void free(void *ptr)
{
    if (ptr)
    {
        check_address(ptr);
    }
}

__attribute__((visibility("default"))) void *realloc(void *ptr, size_t size)
{
    if (size == 0 && ptr)
    {
        free(ptr);
        return NULL;
    }
    void *new_ptr = malloc(size);
    if (!new_ptr)
        return NULL;
    memcpy(new_ptr, ptr, size);
    free(ptr);
    return new_ptr;
}

__attribute__((visibility("default"))) void *calloc(size_t nmemb, size_t size)
{
    size_t tmp = 0;
    if (__builtin_umull_overflow(nmemb, size, &tmp))
        return NULL;
    char *ptr = malloc(nmemb * size);
    if (ptr)
    {
        for (size_t i = 0; i < nmemb; i++)
            ptr[i] = 0;
    }
    return ptr;
}
