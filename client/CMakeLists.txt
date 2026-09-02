cmake_minimum_required(VERSION 3.16)

project(client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(client
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

target_link_libraries(client
    PRIVATE
    Qt6::Widgets
    Qt6::Network
)