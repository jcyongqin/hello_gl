//
// Created by wyq on 2019/3/22.
//

#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
// 包含glad来获取所有的必须OpenGL头文件
#include <glad/glad.h>

namespace imgui {

class Shader {
public:
    // 构造器读取并构建着色器
    Shader(const std::string &vertexPath, const std::string &fragmentPath);

    ~Shader();

    // 使用/激活程序
    void use();

    // attribute Location工具函数
    void VertexAttribPointer(const std::string &attribute, GLint size, GLenum type,
                             GLboolean normalized, GLsizei stride, const void *pointer);

    // uniform工具函数
    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

    void setMat4(const std::string &name, float *pValue) const;

private:
    void checkShaderCompile(unsigned int shader, const char *exInfo);

    void checkProgramLink(unsigned int program);

public:
    // 程序ID
    unsigned int ID;
};

}
