cmake_minimum_required(VERSION 3.16)

project(gui VERSION 0.1 LANGUAGES CXX)

file(GLOB GUI_SOURCES . *.cpp)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(IVoice_client_qt
    ${GUI_SOURCES}
    ${CMAKE_SOURCE_DIR}/include/mainwindow.h
    ${CMAKE_SOURCE_DIR}/include/basewidget.h
    ${CMAKE_SOURCE_DIR}/include/serverbar.h
    ${CMAKE_SOURCE_DIR}/include/sidebar.h
    ${CMAKE_SOURCE_DIR}/include/workspace.h
    ${CMAKE_SOURCE_DIR}/include/registerwindow.h
    ${CMAKE_SOURCE_DIR}/include/loginwindow.h
    ${CMAKE_SOURCE_DIR}/include/settingswidget.h
    ${CMAKE_SOURCE_DIR}/resources.qrc
    ${CMAKE_SOURCE_DIR}/include/core.h
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
