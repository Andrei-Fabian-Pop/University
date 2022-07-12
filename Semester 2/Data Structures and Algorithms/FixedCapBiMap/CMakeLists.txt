cmake_minimum_required(VERSION 3.20)
project(FixedCapBiMap)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(FixedCapBiMap
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        FixedCapBiMap.cpp
        FixedCapBiMap.h
        FixedCapBiMapIterator.cpp
        FixedCapBiMapIterator.h
        ShortTest.cpp
        ShortTest.h)
