cmake_minimum_required(VERSION 3.5)

project(untitled4 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/dialog.cpp
        inc/dialog.h
        src/dialog.ui
        inc/mainwindow.h
        src/mainwindow.ui
        inc/User.h
        src/User.cpp
        src/Movie.cpp inc/Movie.h
        src/QnetworkAcces.cpp
        inc/QnetworkAcces.h )

add_executable(movietest inc/Movie.h src/Movie.cpp)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(untitled4
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET untitled4 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(untitled4 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(untitled4
            ${PROJECT_SOURCES}
        )
    endif()
endif()
target_link_directories(untitled4 PRIVATE ../Database)
target_link_directories(movietest PRIVATE ../Database)
target_include_directories(untitled4 PRIVATE inc)
target_link_libraries(untitled4 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network db_lib)

set_target_properties(untitled4 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS untitled4
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(untitled4)
endif()
