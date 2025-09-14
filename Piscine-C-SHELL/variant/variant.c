#include "variant.h"

#include <stdio.h>
#include <string.h>

static int is_same_value(const struct variant v, union type_any value,
                         enum type type)
{
    if (type == TYPE_INT)
        return value.int_v == v.value.int_v;
    else if (type == TYPE_FLOAT)
        return value.float_v == v.value.float_v;
    else if (type == TYPE_CHAR)
        return value.char_v == v.value.char_v;
    return 0;
}

void variant_display(const struct variant *e)
{
    switch (e->type)
    {
    case TYPE_INT:
        printf("%d\n", e->value.int_v);
        break;
    case TYPE_FLOAT:
        printf("%f\n", e->value.float_v);
        break;
    case TYPE_CHAR:
        printf("%c\n", e->value.char_v);
        break;
    case TYPE_STRING:
        printf("%s\n", e->value.str_v);
        break;
    default:
        printf("WTF?");
    }
}

bool variant_equal(const struct variant *left, const struct variant *right)
{
    if (!left && !right)
        return true;
    if (!left || !right)
        return false;
    if (left->type == right->type && left->type == TYPE_STRING)
    {
        if (!strcmp(left->value.str_v, right->value.str_v))
            return true;
    }
    if (left->type == right->type
        && is_same_value(*left, right->value, left->type))
        return true;
    return false;
}

int variant_find(const struct variant *array, size_t len, enum type type,
                 union type_any value)
{
    int value_to_return = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (array[i].type == type)
        {
            if (type == TYPE_STRING
                && !strcmp(array[i].value.str_v, value.str_v))
                return value_to_return;
            if (is_same_value(array[i], value, type))
                return value_to_return;
        }
        value_to_return++;
    }
    return -1;
}

float variant_sum(const struct variant *array, size_t len)
{
    float sum = 0.;
    for (size_t i = 0; i < len; i++)
    {
        if (array[i].type == TYPE_INT)
            sum += array[i].value.int_v;
        else if (array[i].type == TYPE_FLOAT)
            sum += array[i].value.float_v;
    }
    return sum;
}
