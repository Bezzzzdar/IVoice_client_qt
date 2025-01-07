cmake_minimum_required(VERSION 3.16)

project(core VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/include)
file(GLOB LIBCORE_SOURCES . *.cpp)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(core SHARED
    ${LIBCORE_SOURCES}
    ${CMAKE_SOURCE_DIR}/include/core.h
)
target_compile_definitions(core PRIVATE LIBCORE_EXPORTS)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)

