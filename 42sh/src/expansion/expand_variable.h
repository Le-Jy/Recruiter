#ifndef EXPAND_VARIABLE_H
#define EXPAND_VARIABLE_H

#include "expand_word.h"
#include "expansion.h"

enum expansion_status expand_variable(char *string, size_t *idx, char **res);

#endif /* ! EXPAND_VARIABLE_H */
