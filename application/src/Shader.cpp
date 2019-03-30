//
// Created by wyq on 2019/3/22.
//

#include <Shader.h>

#include "Shader.h"

using namespace std;

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
//======== Shader program ========
    ID = glCreateProgram();

//======== Vertex shader ========
    unsigned int vShader;       // shader id
    std::string vShaderCode;    // shader code
    char *pvShaderCode = nullptr;
    std::ifstream vShaderFile;  // shader file
    // 保证ifstream对象可以抛出异常：
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // 读取Shader file
    try {
        // 打开文件
        vShaderFile.open(vertexPath);
        std::stringstream ShaderStream;
        // 读取文件的缓冲内容到数据流中
        ShaderStream << vShaderFile.rdbuf();
        // 关闭文件处理器
        vShaderFile.close();
        // 转换数据流到string
        vShaderCode = ShaderStream.str();
        pvShaderCode = const_cast<char *>(vShaderCode.c_str());
    }
    catch (std::ifstream::failure &e) {
        std::cerr << "ERROR: Shader file read failed" << std::endl;
    }

    // 编译Shader
    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &pvShaderCode, nullptr);
    glCompileShader(vShader);
    checkShaderCompile(vShader, "Vertex shader");

    // Link shader
    glAttachShader(ID, vShader);
    glDeleteShader(vShader);

//======== Fragment shader ========
    unsigned int fShader;       // shader id
    std::string fShaderCode;    // shader code
    char *pfShaderCode = nullptr;
    std::ifstream fShaderFile;  // shader file
    // 保证ifstream对象可以抛出异常：
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // 读取Shader file
    try {
        // 打开文件
        fShaderFile.open(fragmentPath);
        std::stringstream ShaderStream;
        // 读取文件的缓冲内容到数据流中
        ShaderStream << fShaderFile.rdbuf();
        // 关闭文件处理器
        fShaderFile.close();
        // 转换数据流到string
        fShaderCode = ShaderStream.str();
        pfShaderCode = const_cast<char *>(fShaderCode.c_str());
    }
    catch (std::ifstream::failure &e) {
        std::cerr << "ERROR: Shader file read failed" << std::endl;
    }

    // 编译Shader
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &pfShaderCode, nullptr);
    glCompileShader(fShader);
    checkShaderCompile(fShader, "Fragment shader");

    // Link shader
    glAttachShader(ID, fShader);
    glDeleteShader(fShader);

//======== Link shader program ========
    glLinkProgram(ID);
    checkProgramLink(ID);
}

Shader::~Shader() {
    glDeleteProgram(ID);
}


void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::VertexAttribPointer(const std::string &attribute,
                                 GLint size,
                                 GLenum type,
                                 GLboolean normalized,
                                 GLsizei stride,
                                 const void *pointer) {
    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(this->ID, attribute.c_str());
    if (-1 == posAttrib) {
        std::cout << "WARNING::attribute variable " << attribute << " is not active\n" << std::endl;
    }
    glVertexAttribPointer(static_cast<GLuint>(posAttrib), size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(static_cast<GLuint>(posAttrib));
}

void Shader::checkShaderCompile(unsigned int shader, const char *exInfo) {
    int success;
    int info_len;
    // 检查编译错误（如果有的话）
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);
        char *pInfo = new char[info_len];
        glGetShaderInfoLog(shader, info_len, nullptr, pInfo);
        std::cerr << "Error: Shader compilation failed (" << exInfo << ")\n" << pInfo << std::endl;
        delete[] pInfo;
    }
}

void Shader::checkProgramLink(unsigned int program) {
    int success;
    int info_len;
    // 检查链接错误（如果有的话）
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_len);
        char *pInfo = new char[info_len];
        glGetProgramInfoLog(program, info_len, nullptr, pInfo);
        std::cerr << "Error: Shader link failed\n" << pInfo << std::endl;
        delete[] pInfo;
    }
}

