#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>



static GLuint pos_location;
// An array of 3 vectors which represents 3 vertices
float vertices[] = {
        0.0f, 0.0f, // Vertex 1 (X, Y)
        0.5f, -0.5f, // Vertex 2 (X, Y)
        -0.5f, -0.5f  // Vertex 3 (X, Y)
};

// Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.
static const GLfloat g_uv_buffer_data[] = {0

};

static float screen_width = 0;
static float screen_height = 0;
static GLuint VBO_pos = 0;
static GLuint VBO_color = 0;
static GLuint VAO = 0;
static GLuint ShaderProgram = 0;
static float g_scale = 0.000001f;

void glfw_error_handle(int code, const char *str) {
    printf_s("code:%d,msg:%s", code, str);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    // 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
    // 关闭应用程序
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    screen_width = width;
    screen_height = height;
}

// 从源码创建shader object
GLuint compile_shader(GLenum shaderType, const char *shaderSource);

GLuint link_shader(GLuint programe, GLuint vs_shader, GLuint fs_shader);

static void start();

static void update();

static void render(GLFWwindow);


int main() {

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(1024, 768, "OpenGL", nullptr, nullptr); // Windowed
    if (!window) {
        fprintf(stderr, "Window or context creation failed\n");
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // 设置ViewPort
    glfwSetWindowSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    // ----------------------------- RESOURCES ----------------------------- //

    // Create Vertex Array Object
    GLuint vao;
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    float vertices[] = {
            // Vertex   // Color
            0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,

            0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            -0.5f, 0.5, 0.0f, 0.0f, 1.0f,
            0.5, 0.5f, 0.0f, 1.0f, 0.0f,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create and compile the vertex shader
    Shader program("res/triangle.vs.glsl", "res/triangle.fs.glsl");
    program.VertexAttribPointer("position", 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    program.VertexAttribPointer("color", 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (2 * sizeof(float)));
    program.use();

    glClearColor(0.2f, 0.5f, 0.8f, 1.0f);

    // ---------------------------- RENDERING ------------------------------ //
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen to black
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a triangle from the 3 vertices
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Swap buffers and poll window events
        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }

    // ---------------------------- CLEARING ------------------------------ //
    // Delete allocated resources
//    glDeleteProgram(shaderProgram);

    glDeleteBuffers(1, &vbo);
//    glDeleteVertexArrays(1, &vao);

    // ---------------------------- TERMINATE ----------------------------- //
    // Terminate GLFW
    glfwTerminate();
    return 0;
}


void start() {
    // 设置深蓝色清屏
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // 生成并绑定 VAO
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);

    // 生成并绑定VBO
    glGenBuffers(1, &VBO_pos);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_pos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 声明顶点属性绑定
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

//    glGenBuffers(1, &VBOcolor);
//    glBindBuffer(GL_ARRAY_BUFFER, VBOcolor);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

    // 创建着色器
    ShaderProgram = glCreateProgram();
//    GLuint vs_shader_obj = compile_shader(GL_VERTEX_SHADER, vertexSource);
//    GLuint fs_shader_obj = compile_shader(GL_FRAGMENT_SHADER, fragmentSource);

//    ShaderProgram = link_shader(ShaderProgram, vs_shader_obj, fs_shader_obj);
    if (ShaderProgram == 0) {
        fprintf(stderr, "Shader create fail!");
        exit(1);
    }
    glValidateProgram(ShaderProgram);
    glUseProgram(ShaderProgram);
    pos_location = static_cast<GLuint>(glGetAttribLocation(ShaderProgram, "aPos"));

}

void update() {
    //第一步：创建模型观察投影（MVP）矩阵。任何要渲染的模型都要做这一步。

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) screen_width / screen_height, 0.1f, 100.0f);

    // Or, for an ortho camera :
    //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

    // Camera matrix
    glm::mat4 View = glm::lookAt(
            glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    // Our ModelViewProjection : multiplication of our 3 matrices
//    glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

    //第二步：把MVP传给GLSL

// Get a handle for our "MVP" uniform
// Only during the initialisation
    GLint MatrixID = glGetUniformLocation(ShaderProgram, "MVP");

// Send our transformation to the currently bound shader, in the "MVP" uniform
// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
//    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

}

void render(GLFWwindow *window) {
    // wipe the drawing surface clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(ShaderProgram);
//    glBindVertexArray(VAO);
    // draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // update other events like input handling
    glfwPollEvents();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers(window);

    auto err = glGetError();
    printf_s("err:%lld", err);
/*
// 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void *) 0            // array buffer offset
    );
// Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);

*/


}

// 从源码创建shader object
GLuint compile_shader(GLenum shaderType, const char *shaderSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader == 0) {
        printf("create shader fail,:shader type %d\n", shaderType);
        glDeleteShader(shader);
        return 0;
    }
    const char *shaderCode = shaderSource;
    if (shaderCode == nullptr) {
        return 0;
    }

    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    GLint compileResult = GL_TRUE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
    if (compileResult == GL_FALSE) {
        char szLog[4096];
        GLsizei logLen = 0;
//        glGetInfoLogARB(shader, sizeof(szLog), &logLen, szLog);
        //glGetShaderInfoLog(shader, 1024, &logLen, szLog);
        printf("Compile Shader(%04X) fail error log: %s \nshader code:\n%s\n", shaderType, szLog, shaderCode);
        glDeleteShader(shader);
        shader = 0;
    }
    return shader;
}

GLuint link_shader(GLuint programe, GLuint vs_shader, GLuint fs_shader) {
    if (programe == 0) {
        printf_s("着色器程序不存在\n");
        return 0;
    }
    if (vs_shader == 0 || fs_shader == 0) {
        printf_s("着色器对象不存在\n");
        return 0;
    }
    glAttachShader(programe, vs_shader);
    glAttachShader(programe, fs_shader);

    glLinkProgram(programe);
    glValidateProgram(programe);
    GLint linkResult;
    glGetProgramiv(programe, GL_LINK_STATUS, &linkResult);
    if (linkResult == 0) {
        char szLog[1024];
        GLsizei logLen = 0;
        glGetProgramInfoLog(programe, sizeof(szLog), &logLen, szLog);
        fprintf(stderr, "Link Shader fail error log: '%s' \n", szLog);
        return 0;
    }

    return programe;
}
