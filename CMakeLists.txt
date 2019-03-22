cmake_minimum_required(VERSION 3.10)

get_filename_component(PROJECT_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
project("${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib")

macro(auto_add_subdirectory dir)
    file(GLOB child_dirs RELATIVE ${CMAKE_SOURCE_DIR}/${dir} ${dir}/*)
    foreach (subdir IN LISTS child_dirs)
        if (IS_DIRECTORY ${dir}/${subdir})
            add_subdirectory(${dir}/${subdir})
        endif ()
    endforeach ()
endmacro()


list(APPEND WORKSPACE_INCLUDE_PATH "${CMAKE_SOURCE_DIR}")
auto_add_subdirectory(deps)
MESSAGE("Workspace Include Path: ${WORKSPACE_INCLUDE_PATH}")

add_subdirectory(application)

