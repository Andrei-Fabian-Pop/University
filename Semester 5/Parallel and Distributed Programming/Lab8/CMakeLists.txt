cmake_minimum_required(VERSION 3.27)
project(Lab8)

set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(Lab8 main.cpp
        configurations.h
        timetable_generator.cpp
        timetable_generator.h
        group_timetable.cpp
        group_timetable.h
        timetable_generator_threadded.cpp
        timetable_generator_threadded.h
        timetable_generator_distributed.h
        timetable_generator_distributed.cpp)

target_link_libraries(Lab8 ${MPI_CXX_LIBRARIES})

