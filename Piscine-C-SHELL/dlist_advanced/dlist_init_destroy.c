#include <stdlib.h>

#include "dlist.h"

struct dlist *dlist_init(void)
{
    struct dlist *res = malloc(sizeof(struct dlist));
    if (!res)
        return NULL;
    res->size = 0;
    res->tail = NULL;
    res->head = NULL;
    return res;
}

void dlist_clear(struct dlist *list)
{
    for (size_t i = 0; i < list->size; i++)
    {
        struct dlist_item *tmp = list->head->next;
        free(list->head);
        list->head = tmp;
    }
    list->size = 0;
    list->tail = NULL;
}
