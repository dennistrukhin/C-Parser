//
// Created by Dennis Trukhin on 23/04/2018.
//

#ifndef PARSER_FILEREADER_H
#define PARSER_FILEREADER_H


#include "Lexeme.h"

class FileReader {
private:
    enum {MODE_IDENTIFIER, MODE_NUMBER_CARDINAL, MODE_NUMBER_DECIMAL, MODE_STRING, MODE_OTHER, MODE_LOGIC_OR_ASSIGNMENT};
    int mode = MODE_OTHER;
    int startPos = 0;
    int pos = 0;
    long long int length = 0;
    char * b;
    Lexeme *makeLexemeFromCurrentPositions(int type);
    Lexeme *makeLogicOrAssignmentLexemeFromCurrentPositions();
public:
    explicit FileReader(const char * fileName);

    Lexeme *readLexeme();

    bool isEOF();

    bool charIsAlphaNumeric(char c);
    bool charIsAlpha(char c);
    bool charIsNumeric(char c);
    bool charIsWhiteSpace(char c);
    bool charIsLogicOrAssignment(char c);
};


#endif //PARSER_FILEREADER_H
