#ifndef EXPAND_QUOTE_H
#define EXPAND_QUOTE_H

#include "expand_word.h"

enum expansion_status expand_quote(char *string, size_t *idx, char **res);

#endif /* ! EXPAND_QUOTE_H */
