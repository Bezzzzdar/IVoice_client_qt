cmake_minimum_required(VERSION 3.16)

project(IVoice_client_qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_subdirectory(src/core)
add_subdirectory(src/gui)

include_directories(SYSTEM ${CMAKE_SOURCE_DIR})

set(PROJECT_SOURCES
        src/main.cpp
        src/gui/mainwindow.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(IVoice_client_qt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/gui/mainwindow.cpp src/main.cpp
        include/widgets.h
        src/gui/sidebar.cpp
        src/gui/serverbar.cpp
        src/gui/workspace.cpp
        src/gui/registerwindow.cpp
        src/gui/loginwindow.cpp
        resources.qrc
        include/core.h
        src/gui/basewidget.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET IVoice_client_qt APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(IVoice_client_qt SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(IVoice_client_qt
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(IVoice_client_qt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(IVoice_client_qt PRIVATE core)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.IVoice_client_qt)
endif()
set_target_properties(IVoice_client_qt PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Копирование DLL после сборки
add_custom_command(TARGET IVoice_client_qt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:core>
        $<TARGET_FILE_DIR:IVoice_client_qt>
)

# копирование директории config
add_custom_command(TARGET IVoice_client_qt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/config"
        "$<TARGET_FILE_DIR:IVoice_client_qt>/config"
)

include(GNUInstallDirs)
install(TARGETS IVoice_client_qt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(FILES $<TARGET_FILE:core> DESTINATION ${CMAKE_INSTALL_BINDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(IVoice_client_qt)
endif()
