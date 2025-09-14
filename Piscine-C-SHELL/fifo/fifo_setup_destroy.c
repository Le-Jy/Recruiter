#include <stdlib.h>

#include "fifo.h"

struct fifo *fifo_init(void)
{
    struct fifo *res = malloc(sizeof(struct fifo));
    if (res == NULL)
        return NULL;
    res->tail = NULL;
    res->head = NULL;
    res->size = 0;
    return res;
}

void fifo_clear(struct fifo *fifo)
{
    while (fifo->head)
    {
        struct list *tmp = fifo->head->next;
        free(fifo->head);
        fifo->head = tmp;
    }
    fifo->size = 0;
}

void fifo_destroy(struct fifo *fifo)
{
    fifo_clear(fifo);
    free(fifo);
}
