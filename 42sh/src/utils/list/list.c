#include "list.h"

#include <stdlib.h>
#include <string.h>

struct list *list_prepend(struct list *list, const void *value,
                          size_t data_size)
{
    struct list *elt = malloc(sizeof(struct list));
    if (!elt)
        return NULL;
    elt->data = malloc(data_size);
    if (!elt->data)
    {
        free(elt);
        return NULL;
    }
    memcpy(elt->data, value, data_size);
    elt->next = list;
    return elt;
}

size_t list_length(struct list *list)
{
    size_t len = 0;
    while (list)
    {
        list = list->next;
        len++;
    }

    return len;
}

void list_destroy(struct list *list)
{
    while (list)
    {
        struct list *tmp = list->next;
        free(list->data);
        free(list);
        list = tmp;
    }
}
