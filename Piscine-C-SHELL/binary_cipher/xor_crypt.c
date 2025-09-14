#include "binary_cipher.h"

void my_xor_crypt(void *data, size_t data_len, const void *key, size_t key_len)
{
    unsigned char *data_c = data;
    const unsigned char *key_c = key;
    if (!data || !key)
        return;
    size_t j = 0;
    for (size_t i = 0; i < data_len; i++)
    {
        data_c[i] ^= key_c[j];
        j++;
        if (j == key_len)
            j = 0;
    }
    data = data_c;
}
