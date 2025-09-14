#include <stdio.h>

#include "binary_cipher.h"
int main(void)
{
    unsigned char *data = { 0x54, 0x68, 0x65, 0x20, 0x71, 0x75,
                            0x69, 0x63, 0x6b, 0x20, 0x62, 0x72 };
    const unsigned char key = { 0x01 };
    my_rol_crypt(data, 12, &key, 1);
    unsigned char *p = data;
    for (size_t i = 0; i < 12; i++)
        printf("%c ", p[i]);
