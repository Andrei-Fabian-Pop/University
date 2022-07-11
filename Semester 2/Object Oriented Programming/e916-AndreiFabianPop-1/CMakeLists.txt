cmake_minimum_required(VERSION 3.22)
project(e916_AndreiFabianPop_1)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

set(CMAKE_CXX_STANDARD 14)

add_executable(e916_AndreiFabianPop_1
        main.cpp
        User.h
        User.cpp
        Quastion.h
        Quastion.cpp
        Answer.h
        Answer.cpp
        UserList.h
        UserList.cpp
        userwindow.h
        userwindow.cpp
        userwindow.ui
        Observer.h
        Observer.cpp
        QnA.h
        QnA.cpp searchw.cpp searchw.h searchw.ui)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

target_link_libraries(e916_AndreiFabianPop_1
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )