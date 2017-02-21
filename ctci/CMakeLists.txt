cmake_minimum_required(VERSION 3.5.1)
project(ctci_solutions)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES ch8_ex1.cpp ch16_ex1.cpp ch16_ex2.cpp BoyerMoore.cpp BoyerMoore.h ch16_ex4.cpp)
add_executable(run_tests ${SOURCE_FILES})

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_link_libraries(run_tests gtest gtest_main)
