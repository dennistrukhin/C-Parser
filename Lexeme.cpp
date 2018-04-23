//
// Created by Dennis Trukhin on 23/04/2018.
//

#include <cstdlib>
#include <cstring>
#include "Lexeme.h"

Lexeme::Lexeme(unsigned char *c) {
    int l = 0;
    unsigned char *p = c;
    while (*p != '\0', p++, l++);
    size_t size = (l + 1) * sizeof(unsigned char);
    chr = (unsigned char *) malloc(size);
    memcpy(chr, c, size);
    chr[size] = '\0';
}
