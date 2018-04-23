//
// Created by Dennis Trukhin on 23/04/2018.
//

#ifndef PARSER_FILEREADER_H
#define PARSER_FILEREADER_H


#include "Lexeme.h"

class FileReader {
private:
    char * b;
public:
    explicit FileReader(char * fileName);

    Lexeme *readLexeme();
};


#endif //PARSER_FILEREADER_H
