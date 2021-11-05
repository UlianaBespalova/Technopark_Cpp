cmake_minimum_required(VERSION 3.10)

project(homework_2)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--coverage -ftest-coverage")
set(CMAKE_C_FLAGS "--coverage -ftest-coverage")

include_directories(project/simple project/parallel project/common)

set(SIMPLE_DIR project/simple)
set(PARALLEL_DIR project/parallel)
set(COMMON_DIR project/common)

set(SIMPLE_LIB_SOURCE_FILES ${SIMPLE_DIR}/simple.c)
add_library(simple_library STATIC ${SIMPLE_LIB_SOURCE_FILES})

set(PARALLEL_LIB_SOURCE_FILES ${PARALLEL_DIR}/parallel.c)
add_library(parallel_library SHARED ${PARALLEL_LIB_SOURCE_FILES})

add_executable(main_simple project/main_simple.c)
target_link_libraries(main_simple simple_library)

add_executable(main_parallel project/main_parallel.c)
target_link_libraries(main_parallel parallel_library)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(homework_2 project/test/gtests.cpp)
target_link_libraries(homework_2 ${GTEST_LIBRARIES})
target_link_libraries(homework_2 pthread)
target_link_libraries(homework_2 simple_library)
target_link_libraries(homework_2 parallel_library ${CMAKE_DL_LIBS})