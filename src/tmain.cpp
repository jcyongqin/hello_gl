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
//#include "Shader.h"
//#include "Controller.h"

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

static float screen_width = 800;
static float screen_height = 600;
static GLuint VBO_pos = 0;
static GLuint VBO_color = 0;
static GLuint VAO = 0;
static GLuint ShaderProgram = 0;
static float g_scale = 0.000001f;

void glfw_error_handle(int code, const char *str) {
    printf("code:%d,msg:%s", code, str);
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

int tmain() {
/*
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(1200, 900, "OpenGL", nullptr, nullptr); // Windowed
    if (!window) {
        fprintf(stderr, "Window or context creation failed\n");
    }
    glfwMakeContextCurrent(window);
    */
    /*
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSwapInterval(GLFW_TRUE);
    // 设置ViewPort
    glfwSetWindowSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
     */

    // ----------------------------- RESOURCES ----------------------------- //

    // Vertics Data
    // An array of 3 vectors which represents 3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
    };
    static const GLuint g_element_buffer_data[] = {
        0, 2, 3,
        0, 3, 1,
        6, 0, 1,
        6, 1, 7,
        4, 2, 0,
        4, 0, 6,
        5, 3, 2,
        5, 2, 4,
        7, 1, 3,
        7, 3, 5,
        4, 6, 7,
        4, 7, 5,

    };

    static const GLfloat g_color_buffer_data[] = {
        0.1f, 0.1f, 0.1f,
        0.1f, 0.9f, 0.1f,
        0.9f, 0.1f, 0.1f,
        0.9f, 0.9f, 0.1f,
        0.1f, 0.1f, 0.9f,
        0.1f, 0.9f, 0.9f,
        0.9f, 0.1f, 0.9f,
        0.9f, 0.9f, 0.9f,
    };


    // Create and compile the vertex shader
//    Shader program("res/triangle.vs.glsl", "res/triangle.fs.glsl");
//    program.use();

    // Create Vertex Array Object
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create a Element Buffer Object and copy the vertex data to it
    GLuint elementBuffer;
    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_element_buffer_data), g_element_buffer_data, GL_STATIC_DRAW);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
//    program.VertexAttribPointer("position", 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

    // Create a Color Buffer Object and copy the vertex data to it
    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
//    program.VertexAttribPointer("color", 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

    // load texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
// 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 加载并生成纹理
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("res/container.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    double lastTime = glfwGetTime();
    int nbFrames = 0;
//    Controller ctrler(window);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClearDepth(1.0);
    // 开启深度测试
    glEnable(GL_DEPTH_TEST);
    // Cull triangles which normal is not towards the camera
    //glEnable(GL_CULL_FACE);
    // ---------------------------- RENDERING ------------------------------ //
    while (0) {
//        while (!glfwWindowShouldClose(window)) {
//        ctrler.update();

        // Clear the color buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) screen_width / (float) screen_height,
                                                0.1f, 100.0f);
        // Or, for an ortho camera :
        //glm::mat4 Projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.0f, 100.0f); // In world coordinates

        // Camera matrix
        glm::mat4 View = glm::lookAt(
            glm::vec3(2, 2, 2), // Camera is at (4,3,3), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
        );
//        View = ctrler.getViewMatrix();

        // Model matrix : an identity matrix (model will be at the origin)
        glm::mat4 Model = glm::mat4(1.0f);
        // Our ModelViewProjection : multiplication of our 3 matrices
        glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

        // Trans "MVP" uniform to GLSL
//        program.setMat4("MVP", &mvp[0][0]);

        // Bind VAO
        glBindVertexArray(VertexArrayID);
        // Draw a triangle from the 3 vertices
        glDrawElements(GL_TRIANGLES, sizeof(g_element_buffer_data) / sizeof(GLuint),
                       GL_UNSIGNED_INT, nullptr);

        // Swap buffers and poll window events
//        glfwSwapBuffers(window);
        glfwPollEvents();

        // Measure speed
        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 0.5) { // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%d fps\n", nbFrames);
            nbFrames = 0;
            lastTime += 1.0;
        }
    }

    // ---------------------------- TERMINATE ----------------------------- //
    // Terminate GLFW
    glfwTerminate();
    return 0;
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
    printf("err:%lld", err);
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

