cmake_minimum_required(VERSION 3.16)
#add_executable(dbtest src/dbtest.cpp)

set(CMAKE_CXX_STANDARD 17)
find_package(SqliteOrm CONFIG REQUIRED)
add_library(db_lib SHARED src/db_headers.cpp inc/db_headers.h src/MovieDatabase.cpp inc/MovieDatabase.h)
target_include_directories(db_lib PUBLIC inc)
target_link_libraries(db_lib PUBLIC sqlite_orm::sqlite_orm)
add_executable(dbtest src/dbtest.cpp)
target_include_directories(dbtest PRIVATE inc src)

target_link_libraries(dbtest PRIVATE sqlite_orm::sqlite_orm db_lib)
