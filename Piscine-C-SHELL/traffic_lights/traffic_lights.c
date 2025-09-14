#include "traffic_lights.h"

void init(unsigned char *lights)
{
    *lights = 0;
}

void turn_on(unsigned char *lights, unsigned char light_num)
{
    unsigned char mask = 1 << (light_num - 1);
    *lights |= mask;
}

void turn_off(unsigned char *lights, unsigned char light_num)
{
    unsigned char mask = ~(1 << (light_num - 1));
    *lights &= mask;
}

void next_step(unsigned char *lights)
{
    if (*lights & (1 << 3))
        *lights = (*lights << 1) + 1;
    else
        *lights = *lights << 1;
}

void reverse(unsigned char *lights)
{
    *lights = ~*lights;
}

void swap(unsigned char *lights_1, unsigned char *lights_2)
{
    unsigned char lights_1_tmp = *lights_1;
    unsigned char lights_2_tmp = *lights_2;
    *lights_1 = lights_2_tmp;
    *lights_2 = lights_1_tmp;
}
