cmake_minimum_required(VERSION 3.16)

project(core VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

set(GRPC 0)

if (GRPC)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Protobuf)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Grpc)

    set(PROTO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/proto)
    set(PROTO_GEN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/proto/generated)

    file(MAKE_DIRECTORY ${PROTO_GEN_DIR})

    qt_add_protobuf(core_protobuf_lib
        PROTO_FILES
            ${PROTO_DIR}/auth.proto
        OUTPUT_DIRECTORY ${PROTO_GEN_DIR}
    )

    qt_add_grpc(core_protobuf_client CLIENT
        PROTO_FILES
            ${PROTO_DIR}/auth.proto
        OUTPUT_DIRECTORY ${PROTO_GEN_DIR}
    )
    include_directories(${PROTO_GEN_DIR})
endif()

include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/include)

file(GLOB LIBCORE_SOURCES . *.cpp)

add_library(core SHARED
    ${LIBCORE_SOURCES}
    ${CMAKE_SOURCE_DIR}/include/core.h
)
target_compile_definitions(core PRIVATE LIBCORE_EXPORTS)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)

if(GRPC)
    target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Protobuf)
    target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Grpc)
    target_link_libraries(core PRIVATE core_protobuf_client core_protobuf_lib Qt${QT_VERSION_MAJOR}::Protobuf)
    target_compile_definitions(core PUBLIC GRPC)
endif()

