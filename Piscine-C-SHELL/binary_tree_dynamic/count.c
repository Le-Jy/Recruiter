#include "binary_tree.h"

int size(const struct binary_tree *tree)
{
    int res = 0;
    if (tree)
    {
        res += 1;
        res += size(tree->left);
        res += size(tree->right);
    }
    return res;
}

int max(int h1, int h2)
{
    return (h1 > h2) ? h1 : h2;
}

int height(const struct binary_tree *tree)
{
    if (tree)
    {
        int left_value = height(tree->left);
        int right_value = height(tree->right);
        return max(left_value, right_value) + 1;
    }
    return -1;
}
