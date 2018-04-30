#include <iostream>
#include "FileReader.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "File name argument required");
        return 1;
    }
    auto reader = new FileReader(argv[1]);
    while (!reader->isEOF()) {
        auto l = reader->readLexeme();
        l->dump();
//        break;
    }

}