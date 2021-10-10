cmake_minimum_required(VERSION 3.9.2)
project(Shapes)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -ggdb3 --coverage")

ADD_SUBDIRECTORY (googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(shapes main.c shapes.c)
add_executable(tests tests.cpp shapes.c)

#Link with GoogleTest
target_link_libraries(tests gtest gtest_main m)
target_link_libraries(shapes m)
#===============================================================

