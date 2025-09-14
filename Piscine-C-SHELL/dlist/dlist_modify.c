#include "dlist.h"

int dlist_push_front(struct dlist *list, int element)
{
    if (element < 0)
        return 0;
    struct dlist_item *new = malloc(sizeof(struct dlist_item));
    if (!new)
        return 0;
    new->data = element;
    if (list->size == 0)
    {
        list->head = new;
        list->tail = new;
        new->next = NULL;
        new->prev = NULL;
    }
    else
    {
        new->prev = NULL;
        list->head->prev = new;
        new->next = list->head;
        list->head = new;
    }
    list->size++;
    return 1;
}

int dlist_push_back(struct dlist *list, int element)
{
    if (element < 0)
        return 0;
    struct dlist_item *new = malloc(sizeof(struct dlist_item));
    if (!new)
        return 0;
    new->data = element;
    if (list->size == 0)
    {
        list->head = new;
        list->tail = new;
        new->next = NULL;
        new->prev = NULL;
    }
    else
    {
        new->next = NULL;
        list->tail->next = new;
        new->prev = list->tail;
        list->tail = new;
    }
    list->size++;
    return 1;
}

int dlist_insert_at(struct dlist *list, int element, size_t index)
{
    if (element < 0)
        return -1;
    if (index > list->size)
        return -1;
    if (index == 0)
    {
        dlist_push_front(list, element);
        return 1;
    }
    if (index == list->size)
    {
        dlist_push_back(list, element);
        return 1;
    }

    struct dlist_item *new = malloc(sizeof(struct dlist_item));
    if (!new)
        return -1;
    new->data = element;
    struct dlist_item *tmp = list->head;

    for (size_t i = 0; i < index; i++)
    {
        tmp = tmp->next;
    }
    new->prev = tmp->prev;
    tmp->prev = new;
    new->prev->next = new;
    new->next = tmp;
    list->size++;

    return 1;
}

int dlist_remove_at(struct dlist *list, size_t index)
{
    int value_to_return = -1;
    if (index > list->size - 1 || !list->size)
        return value_to_return;
    struct dlist_item *tmp = list->head;
    for (size_t i = 0; i < index; i++)
    {
        tmp = tmp->next;
    }
    if (index == 0)
    {
        list->head = tmp->next;
        if (list->head != NULL)
            list->head->prev = NULL;
    }
    else if (index == list->size - 1)
    {
        list->tail = tmp->prev;
        if (list->tail != NULL)
        {
            list->tail->next = NULL;
        }
    }
    else
    {
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
    }
    value_to_return = tmp->data;
    free(tmp);
    list->size--;
    return value_to_return;
}

void dlist_map_square(struct dlist *list)
{
    size_t counter = 0;
    struct dlist_item *tmp = list->head;
    while (counter < list->size)
    {
        tmp->data *= tmp->data;
        tmp = tmp->next;
        counter++;
    }
}

void dlist_reverse(struct dlist *list)
{
    struct dlist_item *tmp = NULL;
    struct dlist_item *actual = list->head;

    while (actual)
    {
        tmp = actual->prev;
        actual->prev = actual->next;
        actual->next = tmp;
        actual = actual->prev;
    }
    if (tmp)
    {
        list->tail = list->head;
        list->head = tmp->prev;
    }
}

struct dlist *dlist_split_at(struct dlist *list, size_t index)
{
    if (index > list->size)
        return NULL;
    if (!list->size)
        return dlist_init();
    struct dlist_item *tmp = list->head;
    for (size_t j = 0; j < index; j++)
        tmp = tmp->next;
    struct dlist *newlist = dlist_init();
    newlist->head = tmp;
    newlist->tail = list->tail;
    list->tail = tmp->prev;
    if (index == 0)
        list->head = tmp->prev;
    newlist->head->prev = NULL;
    if (list->tail)
        list->tail->next = NULL;
    newlist->size = list->size - index;
    list->size -= list->size - index;
    return newlist;
}

void dlist_concat(struct dlist *list1, struct dlist *list2)
{
    size_t list2_size = list2->size;
    for (size_t i = 0; i < list2_size; i++)
    {
        dlist_push_back(list1, dlist_remove_at(list2, 0));
    }
}
