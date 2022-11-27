cmake_minimum_required(VERSION 3.19.0)
project(mcpp VERSION 0.1.0)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(REAL_PATH build buildDir)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${buildDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${buildDir})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(REAL_PATH resources resource_dir)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network Core)
find_package(SqliteOrm CONFIG REQUIRED)

add_subdirectory(modules/Database)
add_subdirectory(modules/Logic)
add_subdirectory(modules/RecEngine)
add_subdirectory(modules/UI)


add_subdirectory(testing)

