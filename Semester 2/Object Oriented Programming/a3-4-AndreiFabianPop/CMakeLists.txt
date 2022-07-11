cmake_minimum_required(VERSION 3.20)
project(a3_4_AndreiFabianPop)

set(CMAKE_CXX_STANDARD 14)

add_executable(a3_4_AndreiFabianPop
        src/main.c
        src/ui/ui.h
        src/ui/ui.c
        src/service/service.h
        src/service/service.c
        src/repository/repository.h
        src/repository/repository.c
        src/domain/medicine.h
        src/domain/medicine.c
        src/tests/tests.c
        src/tests/tests.h)
