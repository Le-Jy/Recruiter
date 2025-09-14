#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

struct blk_meta
{
    struct blk_meta *next;
    struct blk_meta *previous;
    size_t size;
    void *chunk;
    size_t blk_size;
    void *free;
    char data[];
};

void *block_allocate(struct blk_meta *blka);
struct blk_meta *blka_alloc(struct blk_meta *blka, size_t size);
void blka_free(struct blk_meta *blk);
struct blk_meta *block_free(struct blk_meta *blk, void *block);
struct blk_meta *blka_pop(struct blk_meta *blka);

#endif /* !ALLOCATOR_H */
