cmake_minimum_required(VERSION 3.10)
project(framework)

set(CMAKE_CXX_STANDARD 17)

add_library(framework SHARED library.cpp library.h)


set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
