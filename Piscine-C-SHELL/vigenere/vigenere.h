#ifndef VIGENERE_H
#define VIGENERE_H

#include <stddef.h>
#include <stdio.h>

void cipher(const char *key, const char *msg, char *res);

void decipher(const char *key, const char *msg, char *res);

#endif /* ! VIGENERE_H */
