cmake_minimum_required(VERSION 3.16)

project(client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network 3DCore 3DExtras)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(client
    main.cpp
    mainwindow.cpp
    mainwindow.h
    resources.qrc
)

target_link_libraries(client PRIVATE Qt6::Widgets Qt6::3DCore Qt6::3DExtras Qt6::3DRender Qt6::Network)