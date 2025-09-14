#include "bst.h"

#include <stdlib.h>

struct bst_node *create_node(int value)
{
    struct bst_node *new_node = malloc(sizeof(struct bst_node));
    if (!new_node)
        return NULL;
    new_node->data = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

static struct bst_node *insert(struct bst_node *tree,
                               struct bst_node *to_insert)
{
    if (!tree->left && !tree->right)
    {
        if (to_insert->data > tree->data)
            tree->right = to_insert;
        else if (to_insert->data < tree->data)
            tree->left = to_insert;
        else
            free(to_insert);
        return tree;
    }
    struct bst_node *node = tree;

    while (node)
    {
        if (node->data > to_insert->data)
        {
            if (node->left)
                node = node->left;
            else
            {
                node->left = to_insert;
                return tree;
            }
        }
        else if (node->data < to_insert->data)
        {
            if (node->right)
                node = node->right;
            else
            {
                node->right = to_insert;
                return tree;
            }
        }
        else
        {
            free(to_insert);
            return tree;
        }
    }
    return tree;
}

struct bst_node *add_node(struct bst_node *tree, int value)
{
    struct bst_node *to_insert = create_node(value);
    if (!to_insert)
        return NULL;
    if (!tree)
        return to_insert;
    return insert(tree, to_insert);
}

struct bst_node *rec(struct bst_node *tree)
{
    if (tree->left)
        tree = rec(tree->left);
    return tree;
}

struct bst_node *delete_node(struct bst_node *tree, int value)
{
    if (!tree)
        return tree;
    if (tree->data < value)
        tree->right = delete_node(tree->right, value);
    else if (tree->data > value)
        tree->left = delete_node(tree->left, value);
    else
    {
        if (tree->left == NULL)
        {
            struct bst_node *tmp = tree->right;
            free(tree);
            return tmp;
        }
        else if (tree->right == NULL)
        {
            struct bst_node *tmp = tree->left;
            free(tree);
            return tmp;
        }
        struct bst_node *tmp = rec(tree->right);
        tree->data = tmp->data;
        tree->right = delete_node(tree->right, tmp->data);
    }
    return tree;
}

const struct bst_node *find(const struct bst_node *tree, int value)
{
    while (tree && tree->data != value)
    {
        if (tree->data < value)
            tree = tree->right;
        else
            tree = tree->left;
    }
    if (!tree)
        return NULL;
    return tree;
}

void free_bst(struct bst_node *tree)
{
    if (!tree)
        return;
    if (tree->left)
        free_bst(tree->left);
    if (tree->right)
        free_bst(tree->right);
    free(tree);
}
