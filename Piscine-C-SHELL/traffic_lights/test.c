#include <criterion/criterion.h>
#include <stdio.h>

#include "traffic_lights.h"

Test(next_step, three)
{
    unsigned char c = 3;
    next_step(&c);
    cr_assert_eq(c, 6);
}

Test(next_step, f)
{
    unsigned char c = 0xf;
    next_step(&c);
    printf("%x\n", c % 16);
    cr_assert_eq(c % 16, 0xf);
}

Test(turn_off, all)
{
    unsigned char c = 0xf;
    turn_off(&c, 1);
    printf("x\n", c % 16);
    cr_assert_eq(c % 16, 0xe);
}
