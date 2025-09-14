#include <stdio.h>
#include <stdlib.h>

#include "fifo.h"

size_t fifo_size(struct fifo *fifo)
{
    return fifo->size;
}

void fifo_push(struct fifo *fifo, int elt)
{
    struct list *new = malloc(sizeof(struct list));
    if (new == NULL)
        return;
    new->data = elt;
    new->next = NULL;

    if (fifo->head == NULL)
    {
        fifo->head = new;
        fifo->tail = new;
    }
    else
    {
        fifo->tail->next = new;
        fifo->tail = new;
    }
    fifo->size++;
}

int fifo_head(struct fifo *fifo)
{
    return fifo->head->data;
}

void fifo_pop(struct fifo *fifo)
{
    if (fifo->size > 0)
    {
        struct list *new_head = fifo->head->next;
        free(fifo->head);
        fifo->head = new_head;
        fifo->size--;
    }
}

void fifo_print(const struct fifo *fifo)
{
    struct list *tmp = fifo->head;
    while (tmp)
    {
        printf("%d\n", tmp->data);
        tmp = tmp->next;
    }
}
