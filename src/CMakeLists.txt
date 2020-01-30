cmake_minimum_required(VERSION 3.10)
project(application)

set(CMAKE_CXX_STANDARD 20)


#aux_source_directory(./ APP_SRC_LIST)
list(APPEND APP_SRC_LIST main.cpp
        framework/Shader.cpp
        framework/Texture.cpp)

# add executable target
add_executable(${PROJECT_NAME} ${APP_SRC_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE ./)

# 查找链接 opengl
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

# 链接子项目 glad
target_link_libraries(${PROJECT_NAME} glad)
# 链接子项目 stb
target_link_libraries(${PROJECT_NAME} stb)


# 查找链接 SDL2
find_package(SDL2 REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

