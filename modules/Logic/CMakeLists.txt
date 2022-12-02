

add_library(RecSys inc/RecommenderSystem.h src/RecommenderSystem.cpp)
target_include_directories(RecSys PUBLIC inc)
target_link_directories(RecSys PUBLIC ../Database)
target_link_libraries(RecSys db_lib)
add_executable(RecDbg src/RecTest.cpp)
target_link_libraries(RecDbg RecSys)
