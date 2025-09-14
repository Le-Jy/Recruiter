#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../utils/hash_map/hash_map.h"
#include "token.h"

struct lexer
{
    FILE *fd;
    FILE *alias_fd;
    bool unalias;
    struct token *next_token;
    struct token *look_ahead;
    struct hash_map *aliases;
};

struct recognition_info
{
    char c;
    bool quoted;
    bool double_quoted;
    bool backquoted;
    bool escape;
    size_t word_size;
    bool exit_loop;
    bool pass_loop;
    bool is_reserved;
    bool is_variable;
    int nb_tomatch;
};

/**
 * @brief Create a new lexer instance for a given input.
 *
 * @param String representing a shell input.
 *
 * @return Lexer structure.
 */
struct lexer *new_lexer(FILE *file);

/**
 * @brief Free a token.
 *
 * @param Lexer to free.
 *
 */
void free_lexer(struct lexer *lexer);

/**
 * @brief Peek the next token to eat for the parser.
 *
 * @param Current lexer.
 *
 * @return Next token to eat.
 */
struct token *peek_token(struct lexer *lexer);

/**
 * @brief Peek the token after next token to eat for the parser in order to
 * have a look ahead.
 *
 * @param Current lexer.
 *
 * @return Look ahead token.
 */
struct token *look_ahead(struct lexer *lexer);

/**
 * @brief Eat the next token for the parser.
 *
 * @param Current lexer.
 *
 * @return The eaten token.
 */
struct token *eat_token(struct lexer *lexer);

#endif /* ! LEXER_H */
