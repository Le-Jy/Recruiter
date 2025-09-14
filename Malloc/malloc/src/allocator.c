#include "allocator.h"

#include <sys/mman.h>
#include <unistd.h>

struct free_list
{
    struct free_list *next;
};

static struct blk_meta *bucket_free(struct blk_meta *blk)
{
    struct blk_meta *to_return = blk;
    size_t nb_blocks = blk->size / blk->blk_size;
    size_t counter = 0;
    struct free_list *list = blk->free;
    while (list && counter < nb_blocks)
    {
        list = list->next;
        counter++;
    }
    if (counter == nb_blocks)
    {
        to_return = blka_pop(blk);
    }
    return to_return;
}

struct blk_meta *blka_alloc(struct blk_meta *blka, size_t size)
{
    size_t new_size =
        (size + sizeof(struct blk_meta) + sysconf(_SC_PAGESIZE) - 1)
        & ~(sysconf(_SC_PAGESIZE) - 1);
    struct blk_meta *new = mmap(NULL, new_size, PROT_READ | PROT_WRITE,
                                MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    new->size = new_size - sizeof(struct blk_meta);
    new->next = blka;
    if (blka)
        blka->previous = new;
    new->previous = NULL;
    new->chunk = new->data;
    new->blk_size = size;
    struct free_list *current = new->chunk;
    char *ch = new->chunk;
    new->free = new->chunk;
    for (size_t i = 1; i < new->size / size; i++)
    {
        void *tmp = ch + i * size;
        current->next = tmp;
        current = current->next;
    }
    return new;
}

void *block_allocate(struct blk_meta *blka)
{
    if (blka->free)
    {
        void *res = blka->free;
        struct free_list *tmp = blka->free;
        blka->free = tmp->next;
        return res;
    }
    return NULL;
}

struct blk_meta *block_free(struct blk_meta *blk, void *block)
{
    struct blk_meta *to_return = blk;
    if (blk && block)
    {
        struct free_list *to_insert = block;
        to_insert->next = blk->free;
        blk->free = to_insert;
        to_return = bucket_free(blk);
    }
    return to_return;
}

void blka_free(struct blk_meta *blk)
{
    munmap(blk, blk->size + sizeof(struct blk_meta));
}

struct blk_meta *blka_pop(struct blk_meta *blka)
{
    struct blk_meta *tmp = blka;
    if (blka->previous)
        blka->previous->next = blka->next;
    if (blka->next)
        blka->next->previous = blka->previous;
    struct blk_meta *to_return = blka;
    if (!blka->next && !blka->previous)
    {
        blka_free(tmp);
        return NULL;
    }
    if (!blka->previous && blka->next)
        to_return = blka->next;
    else
    {
        while (to_return->previous)
            to_return = to_return->previous;
    }
    blka_free(tmp);
    return to_return;
}
