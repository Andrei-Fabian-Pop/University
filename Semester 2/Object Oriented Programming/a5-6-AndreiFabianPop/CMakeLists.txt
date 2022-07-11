cmake_minimum_required(VERSION 3.10)
project(a5_6_AndreiFabianPop)

set(CMAKE_CXX_STANDARD 14)

add_executable(a5_6_AndreiFabianPop
        src/main.cpp
        src/Domain/Tutorial.cpp
        src/Domain/Tutorial.h
        src/UI/UI.cpp
        src/UI/UI.h
        src/Service/Service.cpp
        src/Service/Service.h
        src/DynamicVector/DynamicVector.cpp
        src/DynamicVector/DynamicVector.h
        src/Tests/Tests.cpp
        src/Tests/Tests.h)
