cmake_minimum_required(VERSION 3.21)
project(t1_AndreiFabianPop_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(t1_AndreiFabianPop_1
        src/main.cpp
        src/domain/School.h
        src/domain/School.cpp
        src/Repository/Repository.h
        src/Repository/Repository.cpp
        src/Service/Service.h
        src/Service/Service.cpp
        src/UI/UI.h
        src/UI/UI.cpp)
