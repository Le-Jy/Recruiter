#ifndef EXPAND_WORD_H
#define EXPAND_WORD_H

#include "expansion.h"

void add_char_to_res(char **res, char c);

// enum expansion_status expand_word(char *string, size_t *idx, char **res);
//
enum expansion_status substitution(char *string, size_t *idx, char **res);

enum expansion_status expand_word(char *string, char **res);

#endif /* ! EXPAND_WORD_H */
