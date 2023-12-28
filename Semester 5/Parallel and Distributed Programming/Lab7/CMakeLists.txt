cmake_minimum_required(VERSION 3.21.2)
project(Lab7)

set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(Lab7 main.cpp)
target_link_libraries(Lab7 ${MPI_CXX_LIBRARIES})
