//
// Created by wyq on 2019/3/22.
//

#ifndef HELLO_GL_SHADER_H
#define HELLO_GL_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
// 包含glad来获取所有的必须OpenGL头文件
#include <glad/glad.h>


class Shader {
public:
    // 程序ID
    unsigned int ID;

    // 构造器读取并构建着色器
    Shader(const std::string &vertexPath, const std::string &fragmentPath);

    // 使用/激活程序
    void use();

    // attribute Location工具函数
    void VertexAttribPointer(const std::string &attribute, GLint size, GLenum type,
                             GLboolean normalized, GLsizei stride, const void *pointer);

    // uniform工具函数
    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;
};


#endif //HELLO_GL_SHADER_H
