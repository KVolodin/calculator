cmake_minimum_required(VERSION 3.10)

project(calculator)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

include_directories(include)

add_subdirectory (src)

enable_testing ()
add_subdirectory (test)
