//
// Created by Dennis Trukhin on 23/04/2018.
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "Lexeme.h"

Lexeme::Lexeme(int t) {
    type = t;
}

void Lexeme::dump() {
    std::cout << "[" << type << "] ";
    for (int i = 0; i < length; i++) {
        std::cout << chr[i];
    }
    std::cout << std::endl ;
}

Lexeme::Lexeme(int t, unsigned char *c) {
    type = t;
    int l = 0;
    unsigned char *p = c;
    while (*p != '\0') {
        p++;
        length++;
    }
    size_t size = (length + 1) * sizeof(unsigned char);
    chr = (unsigned char *) malloc(size);
    memcpy(chr, c, size);
}

int Lexeme::getType() {
    return type;
}
