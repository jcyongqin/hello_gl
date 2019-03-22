cmake_minimum_required(VERSION 3.10)
get_filename_component(PROJECT_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
aux_source_directory(src APP_SRC_LIST)

add_executable(${PROJECT_NAME} ${APP_SRC_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE ${WORKSPACE_INCLUDE_PATH})

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glfw)

