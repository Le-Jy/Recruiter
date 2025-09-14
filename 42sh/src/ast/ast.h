#ifndef AST_H
#define AST_H

enum ast_type
{
    // RULES
    AST_LIST,
    AST_AND_OR,
    AST_PIPELINE,
    AST_COMMAND,
    AST_SIMPLE_COMMAND,
    AST_SHELL_COMMAND,
    AST_FUNCDEC,
    AST_REDIRECTION,
    AST_PREFIX,
    AST_ELEMENT,
    AST_COMPOUND_LIST,
    AST_FOR,
    AST_WHILE,
    AST_UNTIL,
    AST_CASE,
    AST_CASE_CLAUSE,
    AST_CASE_ITEM,
    AST_IF,
    AST_ELSE,
    AST_NOT,
    AST_AND,
    AST_OR,
    AST_COMMAND_BLOCK,
    AST_SUBSHELL,

    // TERMINALS
    AST_EOF,
    AST_WORD,
    AST_ASSIGNEMENT_WORD,
    AST_IONUMBER
};

struct ast
{
    char *value;
    enum ast_type type;
    struct ast **children; // NULL TERMINATED ARRAY
};

/**
 * @brief Create a new AST instance.
 *
 * @param type : the type of the new AST.
 *
 * @return The new AST corresponding to the given type.
 */
struct ast *new_ast(enum ast_type type);

/**
 * @brief Free an AST.
 *
 * @param ast: AST to free.
 *
 */
void free_ast(struct ast *ast);

#endif /* ! AST_H */
