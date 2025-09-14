#include "bst_static.h"

#include <stdlib.h>

struct bst *init(size_t capacity)
{
    struct bst *tree = malloc(sizeof(struct bst));
    if (!tree)
        return NULL;
    tree->capacity = capacity;
    tree->size = 0;
    tree->data = calloc(capacity, sizeof(struct value *));
    if (!tree->data)
    {
        free(tree);
        return NULL;
    }
    return tree;
}

void add(struct bst *tree, int value)
{
    if (!tree)
        return;
    size_t i = 0;
    while (i < tree->capacity && tree->data[i])
    {
        if (tree->data[i]->val > value)
            i = 2 * i + 1;
        else if (tree->data[i]->val < value)
            i = 2 * i + 2;
        else
            return;
    }
    if (i >= tree->capacity)
    {
        tree->data = realloc(tree->data, (i + 1) * sizeof(struct value *));
        for (size_t j = tree->capacity; j < i + 1; j++)
            tree->data[j] = NULL;
        tree->capacity = i + 1;
    }
    struct value *val = malloc(sizeof(struct value));
    val->val = value;
    tree->data[i] = val;
    tree->size++;
}

int search(struct bst *tree, int value)
{
    size_t i = 0;
    while (i < tree->capacity && tree->data[i])
    {
        if (tree->data[i]->val > value)
            i = 2 * i + 1;
        else if (tree->data[i]->val < value)
            i = 2 * i + 2;
        else
            return i;
    }
    return -1;
}

void bst_free(struct bst *tree)
{
    if (!tree)
        return;
    for (size_t i = 0; i < tree->capacity; i++)
    {
        free(tree->data[i]);
    }
    free(tree->data);
    free(tree);
}
