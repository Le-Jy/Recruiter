#ifndef EXPANSION_H
#define EXPANSION_H

#include "../utils/hash_map/hash_map.h"
#include "../utils/list/list.h"

enum expansion_status
{
    EXPAND_OK,
    EXPAND_ERROR
};

struct special_var
{
    char *key;
    char *value;
};

struct expansion
{
    struct hash_map *variables;
    struct list *special_vars;
};

void init_expansion(void);

void free_expansion(void);

#endif /* ! EXPANSION_H */
