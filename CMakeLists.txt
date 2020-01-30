cmake_minimum_required(VERSION 3.10)

project(hello_gl)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include_directories(include)

macro(find_subdirectory result dir)
    file(GLOB child_dirs RELATIVE ${CMAKE_SOURCE_DIR}/${dir} ${dir}/*)
    set(dirs_list "")
    foreach (subdir ${child_dirs})
        if (IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${dir}/${subdir})
            list(APPEND dirs_list ${dir}/${subdir})
        endif ()
    endforeach ()
    set(${result} ${dirs_list})
endmacro()

# 递归添加子项目依赖
find_subdirectory(subdirs ./deps)
foreach (subdir ${subdirs})
    add_subdirectory(${subdir})
endforeach ()

# 添加子项目
add_subdirectory(src)
# 拷贝资源文件夹
set(RES_FILE "./res")
add_custom_target(CopyRuntimeFiles ALL
        COMMAND cp -r ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/res
        DEPENDS ${RES_FILE})


## add executable target
#add_executable(${PROJECT_NAME} src/main.cpp)
#
#set(SDL_DIR /usr/local/Cellar/sdl2/2.0.10) # 这个SDL开发包的路径，可以通过brew info sdl2查出来
#
#target_include_directories(${PROJECT_NAME} PUBLIC ${SDL_DIR}/include/) # 添加SDL头文件搜索路径
#
#target_link_directories(${PROJECT_NAME} PUBLIC ${SDL_DIR}/lib/) # 增加SDL链接库目录
#
#target_link_libraries(${PROJECT_NAME} SDL2 SDL2_test SDL2main GLEW "-framework opengl") # 链接目标库
#
#file(COPY ./res DESTINATION . FOLLOW_SYMLINK_CHAIN) # 拷贝资源文件夹
#
##SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework opengl")

#
#
#
###############################################
#cmake_minimum_required(VERSION 3.10)
#get_filename_component(PROJECT_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
#project(${PROJECT_NAME})
#
#set(CMAKE_CXX_STANDARD 14)
#
#include_directories(include)
#aux_source_directory(../src APP_SRC_LIST)
#
#add_executable(${PROJECT_NAME} ${APP_SRC_LIST})
#
#target_include_directories(${PROJECT_NAME} PRIVATE ${WORKSPACE_INCLUDE_PATH})
#
#find_package(OpenGL REQUIRED)
#target_link_libraries(${PROJECT_NAME} OpenGL::GL)
#
#target_link_libraries(${PROJECT_NAME} glad)
#target_link_libraries(${PROJECT_NAME} glfw)
#
