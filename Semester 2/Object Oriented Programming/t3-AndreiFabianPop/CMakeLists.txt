cmake_minimum_required(VERSION 3.22)
project(t3_AndreiFabianPop)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(t3_AndreiFabianPop
        main.cpp Document.h Document.cpp Repository.cpp Repository.h gui.cpp gui.h gui.ui)

target_link_libraries(t3_AndreiFabianPop
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
