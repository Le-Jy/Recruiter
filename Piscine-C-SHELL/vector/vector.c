#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

struct vector *vector_init(size_t n)
{
    struct vector *new_vector = malloc(sizeof(struct vector));
    if (!new_vector)
        return NULL;
    new_vector->size = 0;
    new_vector->capacity = n;
    new_vector->data = calloc(n, sizeof(int));
    if (!new_vector->data)
    {
        free(new_vector);
        return NULL;
    }
    return new_vector;
}

void vector_destroy(struct vector *v)
{
    free(v->data);
    free(v);
}

struct vector *vector_resize(struct vector *v, size_t n)
{
    if (n == v->capacity)
        return v;
    v->data = realloc(v->data, n * sizeof(int));
    if (!v->data)
        return NULL;
    if (v->size > n)
        v->size = n;
    v->capacity = n;
    return v;
}

struct vector *vector_append(struct vector *v, int elt)
{
    if (!v)
        return NULL;
    if (v->size != v->capacity)
    {
        v->data[v->size] = elt;
    }
    else
    {
        v = vector_resize(v, v->capacity * 2);
        v->data[v->size] = elt;
    }
    v->size++;
    return v;
}

void vector_print(const struct vector *v)
{
    if (!v || v->size == 0)
    {
        printf("\n");
        return;
    }

    size_t counter = 0;
    while (counter < v->size - 1)
    {
        printf("%d,", v->data[counter]);
        counter++;
    }
    printf("%d\n", v->data[v->size - 1]);
}

struct vector *vector_reset(struct vector *v, size_t n)
{
    free(v->data);
    v->data = calloc(n, sizeof(int));
    if (!v->data)
        return NULL;
    v->size = 0;
    v->capacity = n;
    return v;
}

struct vector *vector_insert(struct vector *v, size_t i, int elt)
{
    if (!v || i > v->capacity)
        return NULL;

    if (i == v->size)
        vector_append(v, elt);
    else
    {
        if (v->capacity == v->size)
        {
            v = vector_resize(v, 2 * v->capacity);
        }

        v->size += 1;
        for (size_t j = v->capacity - 1; j > i; j--)
        {
            v->data[j] = v->data[j - 1];
        }
        v->data[i] = elt;
    }
    return v;
}

struct vector *vector_remove(struct vector *v, size_t i)
{
    if (!v || i >= v->capacity)
        return NULL;
    if (i == v->size - 1)
    {
        v->size--;
    }
    else
    {
        for (size_t j = i; j < v->capacity - 1; j++)
            v->data[j] = v->data[j + 1];
        v->size--;
    }
    if (v->size < v->capacity / 2)
    {
        v = vector_resize(v, v->capacity / 2);
    }
    return v;
}
