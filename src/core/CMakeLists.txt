cmake_minimum_required(VERSION 3.16)

project(core)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# include_directories(SYSTEM ${CMAKE_SOURCE_DIR})

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(core SHARED
    server.cpp
    user.cpp
    settings.cpp
    ../../include/core.h
)
target_compile_definitions(core PRIVATE LIBCORE_EXPORTS)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)


target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR})
