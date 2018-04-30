//
// Created by Dennis Trukhin on 23/04/2018.
//

#ifndef PARSER_LEXEM_H
#define PARSER_LEXEM_H


class Lexeme {
private:
    int type;
    unsigned char *chr;
    int length = 0;
public:
    enum {
        LEX_CURLY_OPEN, LEX_CURLY_CLOSE, LEX_PAREN_OPEN, LEX_PAREN_CLOSE,
        LEX_SEMICOLON, LEX_INTEGER, LEX_FLOAT, LEX_IDENTIFIER, LEX_STRING,
        LEX_COMMA,
        LEX_ADD, LEX_SUBTRACT, LEX_MULTIPLY, LEX_DIVIDE,
        LEX_ASSIGN, LEX_EQ, LEX_NE, LEX_GT, LEX_LT, LEX_GTE, LEX_LTE,
        LEX_EOF,
    };
    explicit Lexeme(int t);
    explicit Lexeme(int t, unsigned char *c);
    int getType();
    void dump();
};


#endif //PARSER_LEXEM_H
