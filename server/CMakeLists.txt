cmake_minimum_required(VERSION 3.16)

project(server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets 3DCore 3DExtras Network)
add_executable(server main.cpp mainwindow.cpp mainwindow.h resources.qrc)
target_link_libraries(server PRIVATE Qt6::Widgets Qt6::3DCore Qt6::3DExtras Qt6::3DRender Qt6::Network)