#ifndef PARSER_H
#define PARSER_H

#define _POSIX_C_SOURCE 200809L

#include "../ast/ast.h"
#include "../lexer/lexer.h"

enum parser_status
{
    PARSER_OK,
    PARSER_UNEXPECTED_TOKEN
};

#endif /* ! PARSER_H */
