#ifndef EXPAND_BACKSLASH_H
#define EXPAND_BACKSLASH_H

#include <stdbool.h>

#include "expand_word.h"
#include "expansion.h"

enum expansion_status expand_backslash(char *string, size_t *idx, char **res);

#endif /* ! EXPAND_BACKSLASH_H */
