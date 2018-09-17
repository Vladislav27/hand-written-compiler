cmake_minimum_required(VERSION 3.8)
project(hand_written_compiler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(hand_written_compiler ${SOURCE_FILES})