cmake_minimum_required(VERSION 3.10)

get_filename_component(PROJECT_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
project("${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(application)
add_subdirectory(framework)


