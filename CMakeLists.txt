cmake_minimum_required(VERSION 3.10)
project(Parser)

set(CMAKE_CXX_STANDARD 17)

add_executable(Parser main.cpp FileReader.cpp FileReader.h Lexeme.cpp Lexeme.h)