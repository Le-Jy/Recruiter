#define _POSIX_C_SOURCE 200809L

#include "hash_map_funcdec.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hash_map_funcdec *hash_map_funcdec_init(size_t size)
{
    struct hash_map_funcdec *hmap = malloc(sizeof(struct hash_map_funcdec));
    if (!hmap)
        return NULL;

    struct pair_list_funcdec **data =
        calloc(size, sizeof(struct pair_list_funcdec *));
    if (!data)
    {
        free(hmap);
        return NULL;
    }

    hmap->data = data;
    hmap->size = size;

    return hmap;
}

struct ast *hash_map_funcdec_get(const struct hash_map_funcdec *hash_map,
                                 char *key)
{
    if (!hash_map || !hash_map->size)
        return NULL;
    size_t idx = hash_funcdec(key) % hash_map->size;

    struct pair_list_funcdec *list = hash_map->data[idx];

    while (list && strcmp(list->key, key))
    {
        list = list->next;
    }

    if (!list)
        return NULL;
    return list->value;
}

bool hash_map_funcdec_insert(struct hash_map_funcdec *hash_map, char *key,
                             struct ast *value, bool *updated)
{
    if (!hash_map || !hash_map->size)
        return false;

    size_t idx = hash_funcdec(key) % hash_map->size;

    if (hash_map_funcdec_get(hash_map, key))
    {
        struct pair_list_funcdec *list = hash_map->data[idx];

        while (list && strcmp(list->key, key))
        {
            list = list->next;
        }
        free_ast(list->value);
        list->value = value;
        *updated = true;
    }
    else
    {
        struct pair_list_funcdec *elt =
            malloc(sizeof(struct pair_list_funcdec));
        if (!elt)
            return false;

        elt->key = strdup(key);
        elt->value = value;
        elt->next = hash_map->data[idx];
        hash_map->data[idx] = elt;
        *updated = false;
    }

    return true;
}

void hash_map_funcdec_free(struct hash_map_funcdec *hash_map)
{
    if (!hash_map)
        return;
    for (size_t i = 0; i < hash_map->size; i++)
    {
        struct pair_list_funcdec *head = hash_map->data[i];
        while (head)
        {
            free(head->key);
            free_ast(head->value);
            struct pair_list_funcdec *tmp = head->next;
            free(head);
            head = tmp;
        }
    }
    free(hash_map->data);
    free(hash_map);
}

void hash_map_funcdec_dump(struct hash_map_funcdec *hash_map)
{
    for (size_t i = 0; i < hash_map->size; i++)
    {
        if (hash_map->data[i])
        {
            struct pair_list_funcdec *list = hash_map->data[i];

            while (list)
            {
                printf("%s:", list->key);
                list = list->next;
                if (list)
                    printf(", ");
            }
            printf("\n");
        }
    }
}

bool hash_map_funcdec_remove(struct hash_map_funcdec *hash_map, const char *key)
{
    if (!hash_map || !hash_map->size)
        return NULL;

    size_t idx = hash_funcdec(key) % hash_map->size;

    struct pair_list_funcdec *list = hash_map->data[idx];
    if (!list)
        return false;
    if (!strcmp(list->key, key))
    {
        struct pair_list_funcdec *tmp = list->next;
        free(list->key);
        free_ast(list->value);
        free(list);
        hash_map->data[idx] = tmp;
        return true;
    }

    while (list->next && strcmp(list->next->key, key))
    {
        list = list->next;
    }

    if (!list->next)
    {
        if (strcmp(list->key, key))
            return false;
        free(list->key);
        free_ast(list->value);
        free(list);
        hash_map->data[idx] = NULL;
    }
    else
    {
        struct pair_list_funcdec *tmp = list->next;
        list->next = tmp->next;
        free(tmp->key);
        free_ast(tmp->value);
        free(tmp);
    }
    return true;
}
