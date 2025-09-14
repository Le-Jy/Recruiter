#include "list.h"

#include <stdlib.h>
#include <string.h>

struct list *list_prepend(struct list *list, const void *value,
                          size_t data_size)
{
    struct list *new_element = malloc(sizeof(struct list));
    if (!new_element)
        return NULL;
    new_element->data = malloc(sizeof(void *));
    if (!new_element->data)
    {
        free(new_element);
        return NULL;
    }
    memcpy(new_element->data, value, data_size);
    new_element->next = list;
    return new_element;
}

size_t list_length(struct list *list)
{
    size_t res = 0;
    while (list)
    {
        list = list->next;
        res++;
    }
    return res;
}

void list_destroy(struct list *list)
{
    while (list)
    {
        struct list *tmp = list;
        list = list->next;
        free(tmp->data);
        free(tmp);
    }
}
