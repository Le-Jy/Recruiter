#include "token.h"

#include <stdlib.h>

void token_free(struct token *token)
{
    if (!token)
        return;
    if (token->value)
        free(token->value);
    free(token);
}
