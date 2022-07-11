cmake_minimum_required(VERSION 3.20)
project(AlgoGraph_practical1)

set(CMAKE_CXX_STANDARD 14)

add_executable(AlgoGraph_practical1
        main.cpp
        graph.cpp
        graph.h
        cmake-build-debug/example_input.txt
        cmake-build-debug/graph1k.txt
        cmake-build-debug/graph10k.txt
        cmake-build-debug/graph100k.txt
        cmake-build-debug/graph1m.txt)
