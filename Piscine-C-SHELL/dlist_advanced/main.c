#include <stdio.h>

#include "dlist.h"

int main(void)
{
    struct dlist *l1 = dlist_init();
    struct dlist *l2 = dlist_init();
    for (int i = 1; i < 12; i *= 2 + 1)
        dlist_push_front(l1, i);
    for (int i = 1; i < 12; i *= 2)
        dlist_push_front(l2, i);
    dlist_merge(l1, l2);
    printf("%d\n", l1->tail->data);
}
