#include <stdio.h>

#include "dlist.h"

int main(void)
{
    struct dlist *list = dlist_init();
    dlist_get(list, 1);
    dlist_push_front(list, 1);
    dlist_push_front(list, 5);
    dlist_push_front(list, 3);
    dlist_push_back(list, 4);
    dlist_print(list);
    printf("\n");
    struct dlist *list2 = dlist_split_at(list, 0);
    printf("%d\n\n", list->head->data);
    printf("%d\n\n", list->tail->data);

    dlist_print(list2);
    dlist_print(list);

    dlist_clear(list2);
    free(list2);
    dlist_clear(list);
    free(list);
}
