#define _POSIX_C_SOURCE 200809L

#include "hash_map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hash_map *hash_map_init(size_t size)
{
    struct hash_map *hmap = malloc(sizeof(struct hash_map));
    if (!hmap)
        return NULL;

    struct pair_list **data = calloc(size, sizeof(struct pair_list *));
    if (!data)
    {
        free(hmap);
        return NULL;
    }

    hmap->data = data;
    hmap->size = size;

    return hmap;
}

char *hash_map_get(const struct hash_map *hash_map, char *key)
{
    if (!hash_map || !hash_map->size)
        return NULL;
    size_t idx = hash(key) % hash_map->size;

    struct pair_list *list = hash_map->data[idx];

    while (list && strcmp(list->key, key))
    {
        list = list->next;
    }

    if (!list)
        return NULL;
    return list->value;
}

bool hash_map_insert(struct hash_map *hash_map, char *key, char *value)
{
    if (!hash_map || !hash_map->size)
        return false;

    size_t idx = hash(key) % hash_map->size;

    if (hash_map_get(hash_map, key))
    {
        struct pair_list *list = hash_map->data[idx];

        while (list && strcmp(list->key, key))
        {
            list = list->next;
        }
        free(list->value);
        list->value = strdup(value);
    }
    else
    {
        struct pair_list *elt = malloc(sizeof(struct pair_list));
        if (!elt)
            return false;

        elt->key = strdup(key);
        elt->value = strdup(value);
        elt->next = hash_map->data[idx];
        hash_map->data[idx] = elt;
    }

    return true;
}

void hash_map_free(struct hash_map *hash_map)
{
    if (!hash_map)
        return;
    for (size_t i = 0; i < hash_map->size; i++)
    {
        struct pair_list *head = hash_map->data[i];
        while (head)
        {
            free(head->key);
            free(head->value);
            struct pair_list *tmp = head->next;
            free(head);
            head = tmp;
        }
    }
    free(hash_map->data);
    free(hash_map);
}

void hash_map_dump(struct hash_map *hash_map)
{
    for (size_t i = 0; i < hash_map->size; i++)
    {
        if (hash_map->data[i])
        {
            struct pair_list *list = hash_map->data[i];

            while (list)
            {
                printf("%s:", list->key);
                printf(" %s", list->value);
                list = list->next;
                if (list)
                    printf(", ");
            }
            printf("\n");
        }
    }
}

bool hash_map_remove(struct hash_map *hash_map, const char *key)
{
    if (!hash_map || !hash_map->size)
        return NULL;

    size_t idx = hash(key) % hash_map->size;

    struct pair_list *list = hash_map->data[idx];
    if (!list)
        return false;
    if (!strcmp(list->key, key))
    {
        struct pair_list *tmp = list->next;
        free(list->key);
        free(list->value);
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
        free(list->value);
        free(list);
        hash_map->data[idx] = NULL;
    }
    else
    {
        struct pair_list *tmp = list->next;
        list->next = tmp->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
    return true;
}
