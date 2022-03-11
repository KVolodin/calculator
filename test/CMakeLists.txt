cmake_minimum_required(VERSION 3.10)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(
    ../include
    ${GTEST_INCLUDE_DIRS}
)
 
add_executable(run_test test.cpp)
target_link_libraries(run_test ${GTEST_LIBRARIES} Threads::Threads)
