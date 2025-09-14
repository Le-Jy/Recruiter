#include "hash_map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hash_map *hash_map_init(size_t size)
{
    struct hash_map *hash_map = malloc(sizeof(struct hash_map));
    if (!hash_map)
        return NULL;
    hash_map->data = malloc(sizeof(struct pair_list) * size);
    if (!hash_map->data)
    {
        free(hash_map);
        return NULL;
    }
    for (size_t i = 0; i < size; i++)
    {
        hash_map->data[i] = NULL;
    }
    hash_map->size = size;
    return hash_map;
}

bool hash_map_insert(struct hash_map *hash_map, const char *key, char *value,
                     bool *updated)
{
    if (!hash_map || !hash_map->size)
        return false;
    size_t hash_value = hash(key) % hash_map->size;
    struct pair_list *new_element = malloc(sizeof(struct pair_list));
    if (!new_element)
        return false;
    new_element->key = key;
    new_element->value = value;
    new_element->next = NULL;
    if (hash_map->data[hash_value])
    {
        struct pair_list *data = hash_map->data[hash_value];
        while (data)
        {
            if (!strcmp(data->key, key))
            {
                data->value = value;
                *updated = true;
                free(new_element);
                return true;
            }
            data = data->next;
        }
        new_element->next = hash_map->data[hash_value];
        hash_map->data[hash_value] = new_element;
        *updated = false;
        return true;
    }
    else
    {
        hash_map->data[hash_value] = new_element;
        *updated = false;
        return true;
    }
}

void hash_map_free(struct hash_map *hash_map)
{
    if (!hash_map)
        return;
    for (size_t i = 0; i < hash_map->size; i++)
    {
        struct pair_list *tmp = hash_map->data[i];
        while (tmp)
        {
            struct pair_list *tmp2 = tmp;
            tmp = tmp->next;
            free(tmp2);
        }
    }
    free(hash_map->data);
    free(hash_map);
}

void hash_map_dump(struct hash_map *hash_map)
{
    for (size_t i = 0; i < hash_map->size; i++)
    {
        struct pair_list *tmp = hash_map->data[i];
        while (tmp)
        {
            printf("%s: %s", tmp->key, tmp->value);
            tmp = tmp->next;
            if (tmp)
                printf(", ");
            else
                printf("\n");
        }
    }
}

const char *hash_map_get(const struct hash_map *hash_map, const char *key)
{
    if (!hash_map || !hash_map->size)
        return NULL;
    size_t hash_value = hash(key) % hash_map->size;
    if (hash_map->data[hash_value])
    {
        for (struct pair_list *data = hash_map->data[hash_value]; data;
             data = data->next)
        {
            if (!strcmp(data->key, key))
            {
                return data->value;
            }
        }
    }
    return NULL;
}

bool hash_map_remove(struct hash_map *hash_map, const char *key)
{
    if (!hash_map || !hash_map->size)
        return false;
    size_t hash_value = hash(key) % hash_map->size;
    if (hash_map->data[hash_value])
    {
        struct pair_list *data = hash_map->data[hash_value];
        struct pair_list *prev = hash_map->data[hash_value];
        while (data)
        {
            if (!strcmp(data->key, key))
            {
                if (data == hash_map->data[hash_value])
                    hash_map->data[hash_value] = data->next;
                else
                    prev->next = data->next;
                free(data);
                return true;
            }
            prev = data;
            data = data->next;
        }
    }
    return false;
}
