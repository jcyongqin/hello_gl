cmake_minimum_required(VERSION 3.10)
project(stb)

# 定义头文件的路径变量
SET(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDE_PATH})

# 向上传递头文件路径
#if (WORKSPACE_INCLUDE_PATH)
#    message("----")
#    list(APPEND WORKSPACE_INCLUDE_PATH ${INCLUDE_PATH})
#    set(WORKSPACE_INCLUDE_PATH ${WORKSPACE_INCLUDE_PATH} PARENT_SCOPE)
#endif ()

# 生成静态库
add_library(${PROJECT_NAME} STATIC main.cpp)
# 公开静态库的头文件
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

