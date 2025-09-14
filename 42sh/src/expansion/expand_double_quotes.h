#ifndef EXPAND_DOUBLE_QUOTES_H
#define EXPAND_DOUBLE_QUOTES_H

#include "expand_word.h"
#include "expansion.h"

enum expansion_status expand_double_quotes(char *string, size_t *idx,
                                           char **res);

#endif /* ! EXPAND_DOUBLE_QUOTES_H */
