cmake_minimum_required(VERSION 3.9.2)
project(Shapes)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -ggdb3")

enable_testing()
find_package(GTest REQUIRED)

add_executable(shapes main.c shapes.c)
target_link_libraries(shapes m)

#Link with GoogleTest
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(tests tests.cpp shapes.c)
target_link_libraries(tests ${GTEST_LIBRARIES} m pthread)
#===============================================================
