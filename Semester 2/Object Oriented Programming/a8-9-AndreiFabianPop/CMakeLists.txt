cmake_minimum_required(VERSION 3.21)
project(a8_9_AndreiFabianPop)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(a8_9_AndreiFabianPop
        src/main.cpp
        src/UI/UI.h
        src/UI/UI.cpp
        src/Tests/Tests.h
        src/Tests/Tests.cpp
        src/Service/Service.h
        src/Service/Service.cpp
        src/Domain/Tutorial.h
        src/Domain/Tutorial.cpp
        src/Repository/Repository.h
        src/Repository/WatchList.h
        src/ExceptionsAndValidators/Validator.cpp
        src/ExceptionsAndValidators/Validator.h
        src/ExceptionsAndValidators/Exception.cpp
        src/ExceptionsAndValidators/Exception.h
        src/Repository/HTML_WatchList.cpp
        src/Repository/HTML_WatchList.h
        src/Repository/CSV_WatchList.cpp
        src/Repository/CSV_WatchList.h
        src/GUI/GUI.cpp
        src/GUI/GUI.h)


target_link_libraries(a8_9_AndreiFabianPop
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )
