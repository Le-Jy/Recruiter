#ifndef VARIABLES_H
#define VARIABLES_H

#include "expansion.h"

void add_special_var(struct special_var *current_var);

void modify_special_var(struct special_var *current_var);

char *get_special_var(char *key);

void add_var(char *string);

bool remove_var(char *key);

char *get_var(char *key);

char *escape_special_chars(char *string);

#endif /* ! VARIABLES_H */
