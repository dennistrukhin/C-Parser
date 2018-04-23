//
// Created by Dennis Trukhin on 23/04/2018.
//

#ifndef PARSER_LEXEM_H
#define PARSER_LEXEM_H


class Lexeme {
private:
    unsigned char *chr;
public:
    explicit Lexeme(unsigned char *c);
};


#endif //PARSER_LEXEM_H
