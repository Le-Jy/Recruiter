#include "stack.h"

#include <stdlib.h>

struct stack *stack_push(struct stack *s, int a)
{
    struct stack *new = malloc(sizeof(struct stack));
    if (new == NULL)
        return s;
    new->data = a;
    new->next = s;
    return new;
}

struct stack *stack_pop(struct stack *s)
{
    if (s == NULL)
        return NULL;
    struct stack *res = s->next;
    free(s);
    return res;
}

int stack_peek(struct stack *s)
{
    return s->data;
}
