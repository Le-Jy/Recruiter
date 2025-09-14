#include <limits.h>
#include <stddef.h>

#include "binary_tree.h"

int Fdepth(const struct binary_tree *tree)
{
    const struct binary_tree *tree_tmp = tree;
    int depth = 0;
    while (tree_tmp)
    {
        depth++;
        tree_tmp = tree_tmp->left;
    }
    return depth;
}

int is_perfect_rec(const struct binary_tree *tree, int depth, int current_level)
{
    if (!tree)
        return 1;
    if (!tree->left && !tree->right)
        return (depth == current_level + 1);
    if (!tree->left || !tree->right)
        return 0;
    int left_value = is_perfect_rec(tree->left, depth, current_level + 1);
    int right_value = is_perfect_rec(tree->right, depth, current_level + 1);
    return left_value && right_value;
}

int is_perfect(const struct binary_tree *tree)
{
    int depth = Fdepth(tree);
    return is_perfect_rec(tree, depth, 0);
}

int is_complete_rec(const struct binary_tree *tree, int index, int Fsize)
{
    if (!tree)
        return 1;
    if (index >= Fsize)
        return 0;
    int left_value = is_complete_rec(tree->left, index * 2 + 1, Fsize);
    int right_value = is_complete_rec(tree->right, index * 2 + 2, Fsize);
    return left_value && right_value;
}

int is_complete(const struct binary_tree *tree)
{
    int Fsize = size(tree);
    return is_complete_rec(tree, 0, Fsize);
}

int is_degenerate(const struct binary_tree *tree)
{
    if (!tree)
        return 1;
    if (tree->left && tree->right)
        return 0;
    return is_degenerate(tree->left) && is_degenerate(tree->right);
}

int is_full(const struct binary_tree *tree)
{
    if (!tree)
        return 1;
    if (!tree->left && !tree->right)
        return 1;
    if (tree->left && tree->right)
        return is_full(tree->left) && is_full(tree->right);
    return 0;
}

int is_bst_rec(const struct binary_tree *tree, int max, int min)
{
    if (!tree)
        return 1;
    if (tree->data > max || tree->data < min)
        return 0;
    int left_value = is_bst_rec(tree->left, tree->data - 1, min);
    int right_value = is_bst_rec(tree->right, max, tree->data + 1);
    return left_value && right_value;
}

int is_bst(const struct binary_tree *tree)
{
    return is_bst_rec(tree, INT_MAX, INT_MIN);
}
