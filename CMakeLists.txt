cmake_minimum_required(VERSION 3.14)
project(SegTree)

set(CMAKE_CXX_STANDARD 14)

include_directories(SegTree includes)

add_executable(SegTree main.cpp includes/SegTree.hpp)