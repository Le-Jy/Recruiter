#ifndef PRETTY_PRINTER_H
#define PRETTY_PRINTER_H

#include <stdbool.h>

#include "../ast/ast.h"

void pretty_print(struct ast *ast);
void set_pretty_print(bool);

#endif /* ! PRETTY_PRINTER_H */
