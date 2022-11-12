enable_testing()
find_package(GTest)
add_executable(
        hello_test
        hello_test.cc
)
target_link_directories(hello_test PRIVATE ../modules/Database)
target_link_libraries(
        hello_test
        PUBLIC
        db_lib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
