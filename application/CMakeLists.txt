cmake_minimum_required(VERSION 3.10)
project(application)

set(CMAKE_CXX_STANDARD 17)

add_executable(application main.cpp)


include_directories(${CMAKE_SOURCE_DIR})
target_link_libraries(application framework)

set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/bin)
