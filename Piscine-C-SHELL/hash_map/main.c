#include <stdio.h>

#include "hash_map.h"

int main(void)
{
    bool updated = false;
    struct hash_map *hs = hash_map_init(8);
    hash_map_insert(hs, "key9", "gotze", &updated);
    hash_map_insert(hs, "key1", "grec", &updated);
    hash_map_insert(hs, "key10", "grec", &updated);
    hash_map_dump(hs);
    printf("%s\n", hash_map_get(hs, "key9"));
    hash_map_remove(hs, "key9");
    hash_map_dump(hs);
    hash_map_free(hs);
}
