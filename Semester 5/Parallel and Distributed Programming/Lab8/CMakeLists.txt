cmake_minimum_required(VERSION 3.27)
project(Lab8)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab8 main.cpp
        configurations.h
        timetable_generator.cpp
        timetable_generator.h
        group_timetable.cpp
        group_timetable.h)
