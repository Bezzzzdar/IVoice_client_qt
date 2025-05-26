cmake_minimum_required(VERSION 3.16)

project(gui VERSION 0.1 LANGUAGES CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB GUI_SOURCES  *.cpp)
file(GLOB GUI_HEADERS ${CMAKE_SOURCE_DIR}/include/*.h)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(IVoice_client_qt
    ${GUI_SOURCES}
    ${GUI_HEADERS}
    ${CMAKE_SOURCE_DIR}/resources.qrc
)
target_link_libraries(IVoice_client_qt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(IVoice_client_qt PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(IVoice_client_qt PRIVATE core)

add_custom_command(TARGET IVoice_client_qt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:core>
        $<TARGET_FILE_DIR:IVoice_client_qt>
)

add_custom_command(TARGET IVoice_client_qt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/config"
        "$<TARGET_FILE_DIR:IVoice_client_qt>/config"
)
