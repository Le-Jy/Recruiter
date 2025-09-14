#include <stdio.h>

#include "bst.h"
#include "bst_static.h"

int main(void)
{
    struct bst *tree = init(0);
    for (int i = 0; i < 5; i++)
        add(tree, i);
    for (size_t i = 0; i < tree->capacity; i++)
    {
        if (tree->data[i])
            printf("%d", tree->data[i]->val);
        else
            printf("0");
    }
    printf("\n");
    bst_free(tree);
}
