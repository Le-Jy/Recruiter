#ifndef TOKEN_H
#define TOKEN_H

enum token_type
{
    // Reserved Word
    TOKEN_IF, // 'if'
    TOKEN_THEN, // 'then'
    TOKEN_ELIF, // 'elif'
    TOKEN_ELSE, // 'else'
    TOKEN_FI, // 'fi'
    TOKEN_WHILE, // 'while'
    TOKEN_FOR, // 'for'
    TOKEN_IN, // 'in'
    TOKEN_UNTIL, // 'until'
    TOKEN_DO, // 'do'
    TOKEN_DONE, // 'done'
    TOKEN_CASE,
    TOKEN_ESAC,
    TOKEN_NOT, // '!'
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LPAR,
    TOKEN_RPAR,

    // Regular symbol
    TOKEN_NEWLINE, // '\n'
    TOKEN_SEMICOLON, // ';'
    TOKEN_EOF, // '\0'
    TOKEN_WORD, // Anything else
    TOKEN_ASSIGNMENT_WORD,
    TOKEN_IONUMBER, // IONUMBER
    TOKEN_ERROR, // In case of error

    // Operators
    TOKEN_OPERATOR
};

struct token
{
    enum token_type type;
    char *value; // Only if type = TOKEN_WORD
};

/**
 * @brief free a token allocated by the lexer.
 *
 * @param token to free.
 */
void token_free(struct token *token);

#endif /* ! TOKEN_H */
