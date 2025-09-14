#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H

#include "lexer/lexer.h"

int parse_execute_loop(struct lexer *lexer);

void set_specials_variables(void);

#endif /* ! MAIN_LOOP_H */
