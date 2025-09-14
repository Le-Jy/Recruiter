#ifndef EXEC_WORD_H
#define EXEC_WORD_H

#include "../ast/ast.h"

/**
 * @brief Visits the "word" rule in the ast.
 *
 * Handles the logic for processing "word" rule in the grammar.
 *
 * @param Pointer to the AST node representing the "else" rule.
 * @return The string contained in the word node.
 */
char *visit_word(struct ast *ast);

void free_word(char *word);

#endif /* ! EXEC_WORD_H */
