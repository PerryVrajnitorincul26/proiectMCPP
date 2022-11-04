cmake_minimum_required(VERSION 3.0.0)
project(mcpp VERSION 0.1.0)

add_subdirectory(modules/Database)
add_subdirectory(modules/Logic)
add_subdirectory(modules/RecEngine)
add_subdirectory(modules/UI)

include(CTest)
enable_testing()



include(CPack)
