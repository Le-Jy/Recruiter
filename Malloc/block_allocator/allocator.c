#include "allocator.h"

#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

struct blk_allocator *blka_new(void)
{
    struct blk_allocator *res = calloc(1, sizeof(struct blk_allocator));
    return res;
}

struct blk_meta *blka_alloc(struct blk_allocator *blka, size_t size)
{
    size_t new_size =
        (size + sizeof(struct blk_meta) + sysconf(_SC_PAGESIZE) - 1)
        & ~(sysconf(_SC_PAGESIZE) - 1);
    struct blk_meta *new = mmap(NULL, new_size, PROT_READ | PROT_WRITE,
                                MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    new->size = new_size - sizeof(struct blk_meta);
    new->next = blka->meta;
    blka->meta = new;
    return new;
}

void blka_free(struct blk_meta *blk)
{
    munmap(blk, blk->size + sizeof(struct blk_meta));
}

void blka_pop(struct blk_allocator *blka)
{
    struct blk_meta *tmp = blka->meta;
    if (!tmp)
        return;
    blka->meta = tmp->next;
    blka_free(tmp);
}

void blka_delete(struct blk_allocator *blka)
{
    while (blka->meta)
        blka_pop(blka);
    free(blka);
}
