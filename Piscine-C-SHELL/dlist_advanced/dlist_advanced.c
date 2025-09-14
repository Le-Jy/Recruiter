#include "dlist.h"

void dlist_shift(struct dlist *list, int offset)
{
    if (!list || !offset || list->size == 1)
        return;
    if (offset < 0)
    {
        for (int i = offset; i < 0; i++)
            dlist_push_back(list, dlist_remove_at(list, 0));
    }
    else
    {
        for (int i = 0; i < offset; i++)
            dlist_push_front(list, dlist_remove_at(list, list->size - 1));
    }
}

int dlist_add_sort(struct dlist *list, int element)
{
    if (!list)
        return -1;
    if (!list->size)
        return dlist_push_back(list, element);
    struct dlist_item *tmp = list->head;
    size_t i = 0;
    for (; i < list->size; i++)
    {
        if (tmp->data < element)
            tmp = tmp->next;
        else
            break;
    }
    return dlist_insert_at(list, element, i);
}

int dlist_remove_eq(struct dlist *list, int element)
{
    if (!list || !list->size)
        return 0;
    struct dlist_item *tmp = list->head;
    size_t i = 0;
    for (; i < list->size; i++)
    {
        if (tmp->data != element)
            tmp = tmp->next;
        else
            break;
    }
    if (i == list->size)
        return 0;
    if (dlist_remove_at(list, i) != -1)
        return 1;
    return 0;
}

void dlist_sort(struct dlist *list)
{
    if (!list || !list->head)
        return;
    int sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        struct dlist_item *l1 = list->head;
        struct dlist_item *l2 = list->head->next;
        while (l2)
        {
            if (l1->data > l2->data)
            {
                int tmp = l1->data;
                l1->data = l2->data;
                l2->data = tmp;
                sorted = 0;
            }
            l1 = l1->next;
            l2 = l2->next;
        }
    }
}

void dlist_merge(struct dlist *list1, struct dlist *list2)
{
    dlist_concat(list1, list2);
    dlist_clear(list2);
    dlist_sort(list1);
}

size_t min(size_t i1, size_t i2)
{
    return (i1 > i2) ? i2 : i1;
}

size_t max(size_t i1, size_t i2)
{
    return (i1 > i2) ? i1 : i2;
}

size_t rec(struct dlist *list1, struct dlist *list2, size_t ind1, size_t ind2)
{
    if (min(ind1, ind2) == 0)
        return max(ind1, ind2);
    size_t first = rec(list1, list2, ind1 - 1, ind2) + 1;
    size_t second = rec(list1, list2, ind1, ind2 - 1) + 1;
    size_t third = rec(list1, list2, ind1 - 1, ind2 - 1);
    if (dlist_get(list1, ind1 - 1) != dlist_get(list2, ind2 - 1))
        third++;
    return min(min(first, second), third);
}

unsigned int dlist_levenshtein(struct dlist *list1, struct dlist *list2)
{
    return rec(list1, list2, list1->size, list2->size);
}
