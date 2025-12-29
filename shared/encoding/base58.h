#ifndef BASE58_H
#define BASE58_H

#include <stdbool.h>
#include <stddef.h>

bool b58tobin(void *bin, size_t *binszp, const char *b58, size_t b58sz);
bool b58enc(char *b58, size_t *b58sz, const void *bin, size_t binsz);

#endif
