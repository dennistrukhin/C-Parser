//
// Created by Dennis Trukhin on 23/04/2018.
//

#include <fstream>
#include "FileReader.h"

FileReader::FileReader(char *fileName) {
    std::ifstream file;
    file.open(fileName);
    file.seekg(file.end);
    long long int length = file.tellg();
    file.seekg(file.beg);
    b = (char *) malloc(sizeof(char) * length);
    file.read(b, length);
}

Lexeme *FileReader::readLexeme() {
    return nullptr;
}
