//
// Created by Dennis Trukhin on 23/04/2018.
//

#include <fstream>
#include <iostream>
#include "FileReader.h"

FileReader::FileReader(const char *fileName) {
    std::ifstream file;
    std::cout << "File name: " << fileName << std::endl;
    file.open(fileName, std::istream::binary);
    file.seekg(0, file.end);
    length = file.tellg();
    std::cout << "Length of file: " << length << std::endl;
    file.seekg(0, file.beg);
    b = (char *) malloc(sizeof(char) * length);
    file.read(b, length);
}

Lexeme *FileReader::readLexeme() {
    while (true) {
        if (pos == length) {
            break;
        }
        // Строки
        if (b[pos] == '"' && mode != MODE_STRING) {
            mode = MODE_STRING;
            pos++;
            continue;
        }
        if (b[pos] == '"' && mode == MODE_STRING) {
            mode = MODE_OTHER;
            pos++;
            return makeLexemeFromCurrentPositions(Lexeme::LEX_STRING);
        }
        if (mode == MODE_STRING) {
            pos++;
            continue;
        }

        // Идентификаторы
        if (charIsAlpha(b[pos]) && mode == MODE_OTHER) {
            mode = MODE_IDENTIFIER;
            continue;
        }
        if (charIsAlphaNumeric(b[pos]) && mode == MODE_IDENTIFIER) {
            pos++;
            continue;
        }
        if (!charIsAlphaNumeric(b[pos]) && mode == MODE_IDENTIFIER) {
            mode = MODE_OTHER;
            return makeLexemeFromCurrentPositions(Lexeme::LEX_IDENTIFIER);
        }

        // Числа
        if (charIsNumeric(b[pos]) && mode == MODE_OTHER) {
            mode = MODE_NUMBER_CARDINAL;
            continue;
        }
        if (b[pos] == '.' && mode == MODE_OTHER) {
            mode = MODE_NUMBER_DECIMAL;
            continue;
        }
        if (charIsNumeric(b[pos]) && (mode == MODE_NUMBER_CARDINAL || mode == MODE_NUMBER_DECIMAL)) {
            pos++;
            continue;
        }
        if (b[pos] == '.' && mode == MODE_NUMBER_CARDINAL) {
            pos++;
            mode = MODE_NUMBER_DECIMAL;
            continue;
        }
        if (mode == MODE_NUMBER_CARDINAL && !charIsNumeric(b[pos]) && b[pos] != '.') {
            mode = MODE_OTHER;
            return makeLexemeFromCurrentPositions(Lexeme::LEX_INTEGER);
        }
        if (mode == MODE_NUMBER_DECIMAL && !charIsNumeric(b[pos]) && b[pos] != '.') {
            mode = MODE_OTHER;
            return makeLexemeFromCurrentPositions(Lexeme::LEX_FLOAT);
        }

        // Логические операторы и присваивание
        if (mode == MODE_OTHER && charIsLogicOrAssignment(b[pos])) {
            mode = MODE_LOGIC_OR_ASSIGNMENT;
            pos++;
            continue;
        }
        if (mode == MODE_LOGIC_OR_ASSIGNMENT && !charIsLogicOrAssignment(b[pos])) {
            mode = MODE_OTHER;
            return makeLogicOrAssignmentLexemeFromCurrentPositions();
        }

        if (mode == MODE_OTHER && b[pos] == '{') {
            pos++;
            return makeLexemeFromCurrentPositions(Lexeme::LEX_CURLY_OPEN);
        }
        if (mode == MODE_OTHER && b[pos] == '}') {
            pos++;
            return makeLexemeFromCurrentPositions(Lexeme::LEX_CURLY_CLOSE);
        }
        if (mode == MODE_OTHER && b[pos] == '(') {
            pos++;
            return makeLexemeFromCurrentPositions(Lexeme::LEX_PAREN_OPEN);
        }
        if (mode == MODE_OTHER && b[pos] == ')') {
            pos++;
            return makeLexemeFromCurrentPositions(Lexeme::LEX_PAREN_CLOSE);
        }
        if (mode == MODE_OTHER && b[pos] == ',') {
            pos++;
            return makeLexemeFromCurrentPositions(Lexeme::LEX_COMMA);
        }
        if (mode == MODE_OTHER && b[pos] == ';') {
            pos++;
            return makeLexemeFromCurrentPositions(Lexeme::LEX_SEMICOLON);
        }
        if (mode == MODE_OTHER && b[pos] == '+') {
            pos++;
            return makeLexemeFromCurrentPositions(Lexeme::LEX_ADD);
        }
        if (mode == MODE_OTHER && b[pos] == '-') {
            pos++;
            return makeLexemeFromCurrentPositions(Lexeme::LEX_SUBTRACT);
        }
        if (mode == MODE_OTHER && b[pos] == '*') {
            pos++;
            return makeLexemeFromCurrentPositions(Lexeme::LEX_MULTIPLY);
        }
        if (mode == MODE_OTHER && b[pos] == '/') {
            pos++;
            return makeLexemeFromCurrentPositions(Lexeme::LEX_DIVIDE);
        }
        if (mode == MODE_OTHER && b[pos] == '/') {
            pos++;
            return makeLexemeFromCurrentPositions(Lexeme::LEX_DIVIDE);
        }

        // Пробельные символы пропускаем, так как это уже точно не строка
        if (charIsWhiteSpace(b[pos])) {
            startPos++;
            pos++;
            continue;
        }
    }
    return new Lexeme(Lexeme::LEX_EOF);
}

bool FileReader::charIsAlphaNumeric(const char c) {
    return charIsAlpha(c) || charIsNumeric(c);
}

bool FileReader::charIsAlpha(const char c) {
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
}

bool FileReader::charIsNumeric(const char c) {
    return '0' <= c && c <= '9';
}

bool FileReader::charIsWhiteSpace(char c) {
    return isspace(c) > 0;
}

bool FileReader::isEOF() {
    return pos >= length;
}

Lexeme *FileReader::makeLexemeFromCurrentPositions(int type) {
    size_t lexemeLength = sizeof(unsigned char) * (pos - startPos);
    auto *lc = (unsigned char *) malloc(lexemeLength + 1);
    memcpy(lc, b + startPos, lexemeLength);
    lc[lexemeLength] = '\0';
    startPos = pos;
    return new Lexeme(type, lc);
}

bool FileReader::charIsLogicOrAssignment(char c) {
    return c == '=' || c == '<' || c == '>' || c == '!';
}

Lexeme *FileReader::makeLogicOrAssignmentLexemeFromCurrentPositions() {
    if (pos - startPos == 1) {
        switch (b[startPos]) {
            case '=':
                return makeLexemeFromCurrentPositions(Lexeme::LEX_ASSIGN);
            case '<':
                return makeLexemeFromCurrentPositions(Lexeme::LEX_LT);
            case '>':
                return makeLexemeFromCurrentPositions(Lexeme::LEX_GT);
            default:
                throw std::exception();
        }
    }
    if (pos - startPos == 2) {
        if (b[startPos] == '=' && b[startPos + 1] == '=') {
            return makeLexemeFromCurrentPositions(Lexeme::LEX_EQ);
        }
        if (b[startPos] == '!' && b[startPos + 1] == '=') {
            return makeLexemeFromCurrentPositions(Lexeme::LEX_NE);
        }
        if (b[startPos] == '>' && b[startPos + 1] == '=') {
            return makeLexemeFromCurrentPositions(Lexeme::LEX_GTE);
        }
        if (b[startPos] == '<' && b[startPos + 1] == '=') {
            return makeLexemeFromCurrentPositions(Lexeme::LEX_LTE);
        }
        throw std::exception();
    }
    throw std::exception();
}
