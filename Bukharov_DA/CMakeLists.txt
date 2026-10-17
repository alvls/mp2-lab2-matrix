cmake_minimum_required(VERSION 3.15)
project(DynamicMatrixLab CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gtest)

add_library(gtest STATIC gtest/gtest-all.cc)

file(GLOB TEST_SOURCES "test/*.cpp")
add_executable(run_tests ${TEST_SOURCES})

target_link_libraries(run_tests PRIVATE gtest pthread)

file(GLOB SAMPLE_SOURCES "samples/*.cpp")
add_executable(matrix_sample ${SAMPLE_SOURCES})
