#include "vigenere.h"

#include <stddef.h>

char to_up_case(char c1)
{
    return (c1 >= 'a' && c1 <= 'z') ? c1 - 'a' + 'A' : c1;
}

void cipher(const char *key, const char *msg, char *res)
{
    size_t i = 0;
    size_t j = 0;
    while (msg[i])
    {
        char msgc = to_up_case(msg[i]);
        if (msgc < 'A' || msgc > 'Z')
        {
            res[i] = msg[i];
            i++;
            continue;
        }

        char keyc = to_up_case(key[j]);
        res[i] = (msgc - 'A' + keyc - 'A') % 26 + 'A';
        j++;
        i++;
        if (!key[j])
            j = 0;
    }
    res[i] = '\0';
}

void decipher(const char *key, const char *msg, char *res)
{
    size_t i = 0;
    size_t j = 0;
    while (msg[i])
    {
        char msgc = to_up_case(msg[i]);
        if (msgc < 'A' || msgc > 'Z')
        {
            res[i] = msg[i];
            i++;
            continue;
        }

        char keyc = to_up_case(key[j]);
        res[i] = (msgc - keyc + 26) % 26 + 'A';
        j++;
        i++;
        if (!key[j])
            j = 0;
    }
    res[i] = '\0';
}
