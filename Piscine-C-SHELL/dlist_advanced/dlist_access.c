#include <stdio.h>

#include "dlist.h"

void dlist_print(const struct dlist *list)
{
    struct dlist_item *tmp = list->head;
    size_t elt_counter = 0;
    while (elt_counter < list->size)
    {
        printf("%d\n", tmp->data);
        tmp = tmp->next;
        elt_counter++;
    }
}

size_t dlist_size(const struct dlist *list)
{
    return list->size;
}

int dlist_get(const struct dlist *list, size_t index)
{
    if (list->size - 1 < index || list->size == 0)
        return -1;

    struct dlist_item *tmp = list->head;
    for (size_t i = 0; i != index; i++)
    {
        tmp = tmp->next;
    }
    return tmp->data;
}

int dlist_find(const struct dlist *list, int element)
{
    int index = 0;
    struct dlist_item *tmp = list->head;
    while (tmp)
    {
        if (tmp->data == element)
            return index;
        index++;
        tmp = tmp->next;
    }
    return -1;
}

struct dlist *dlist_copy(const struct dlist *list)
{
    struct dlist *deep_copy = dlist_init();
    if (!deep_copy)
        return NULL;
    struct dlist_item *tmp = list->head;
    for (size_t i = 0; i < list->size; i++)
    {
        if (!dlist_push_back(deep_copy, tmp->data))
            return NULL;
        tmp = tmp->next;
    }
    return deep_copy;
}
