#ifndef HASH_MAP_FUNCDEC_H
#define HASH_MAP_FUNCDEC_H

#include <stdbool.h>
#include <stddef.h>

#include "../../ast/ast.h"

struct pair_list_funcdec
{
    char *key;
    struct ast *value;
    struct pair_list_funcdec *next;
};

struct hash_map_funcdec
{
    struct pair_list_funcdec **data;
    size_t size;
};

size_t hash_funcdec(const char *str);
struct hash_map_funcdec *hash_map_funcdec_init(size_t size);
bool hash_map_funcdec_insert(struct hash_map_funcdec *hash_map, char *key,
                             struct ast *value, bool *updated);
void hash_map_funcdec_free(struct hash_map_funcdec *hash_map);
void hash_map_funcdec_dump(struct hash_map_funcdec *hash_map);
struct ast *hash_map_funcdec_get(const struct hash_map_funcdec *hash_map,
                                 char *key);
bool hash_map_funcdec_remove(struct hash_map_funcdec *hash_map,
                             const char *key);

#endif /* ! HASH_MAP_FUNCDEC_H */
