cmake_minimum_required(VERSION 3.26)
project(Lab4)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab4 main.cpp
        FiniteAutomata.cpp
        FiniteAutomata.h
        Scanner.h
        Scanner.cpp
        SymbolTable.h
        SymbolTable.cpp)
