
#include <iostream>
#include <thread>
#include <cstdlib>

#include <unistd.h>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <stb_image.h>

#include "framework/Shader.h"

using std::cout, std::endl;

namespace imgui {

const int WIDTH = 640, HEIGHT = 580; // SDL窗口的宽和高

// 顶点数据
float vertices[] = {
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};

float vertices_color[] = {
    // 位置              // 颜色
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // 左下
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // 顶部
};

// 顶点索引
unsigned int indices[] = { // 注意索引从0开始!
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};

const float texCoords[] = {
    0.0f, 0.0f, // 左下角
    1.0f, 0.0f, // 右下角
    0.5f, 1.0f // 上中
};

int _tmain(int argc, char *argv[]) {
    char path[128];
    getcwd(path, 128);
    cout << "path:" << path << endl;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { // 初始化SDL
        cout << "SDL could not initialized with error: " << SDL_GetError() << endl;
        return -1;
    }

    //Use OpenGL 3.3 core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // use these two lines instead of the commented one
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // *new*

    atexit(SDL_Quit);// 注册退出函数，释放资源

    // Create window
    SDL_Window *window = SDL_CreateWindow(
        "Hello SDL world!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
        SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (nullptr == window) {
        cout << "SDL could not create window with error: " << SDL_GetError() << endl;
        return -1;
    }

    // Create OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    if (nullptr == glContext) {
        // Display error message
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Initialize glad
    if (0 == gladLoadGL()) {
        cout << "Failed to init glad " << endl;
        return -3;
    }
    int MAJOR_VERSION = 0;
    int MINOR_VERSION = 0;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &MAJOR_VERSION);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &MINOR_VERSION);
    std::string glVersion = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    cout << "opengl version: " << MAJOR_VERSION << "." << MINOR_VERSION << "\n" << glVersion << endl;

    SDL_Event windowEvent; // SDL窗口事件
    SDL_Surface *screen = SDL_GetWindowSurface(window);
    glViewport(0, 0, WIDTH, HEIGHT);


    // 1. 绑定VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // 2. 绑定VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    // 0. 复制顶点数组到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 1. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // 3. 绑定EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 编译着色器
    Shader shader("../res/triangle.vs.glsl", "../res/triangle.fs.glsl");

    // 2. 当我们渲染一个物体时要使用着色器程序
    shader.use();

    glBindVertexArray(VAO);
//    glDrawArrays(GL_TRIANGLES, 0, 3);


    // main loop
    bool quit = false;
    do {
        SDL_GL_SwapWindow(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

//        glDrawArrays(GL_TRIANGLES, 0, 3);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        if (SDL_PollEvent(&windowEvent)) { // 对当前待处理事件进行轮询。
            if (SDL_QUIT == windowEvent.type) { // 如果事件为推出SDL，结束循环。
                cout << "SDL quit!!" << endl;
                quit = true;
            }
            if (SDL_WINDOWEVENT == windowEvent.type) {
//                SDL_Rect rect = {10, 10, 200, 300};
//                SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 90, 120));
//                SDL_UpdateWindowSurface(window);
            }
        }

    } while (not quit);

    SDL_DestroyWindow(window); // 推出SDL窗体
    SDL_Quit();

    return 0;
}

}

int main(int argc, char *argv[]) {
    return imgui::_tmain(argc, argv);
/*
    while (true) {
        bool has_event = SDL_HasEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
        if (not has_event) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        if (SDL_PollEvent(&windowEvent)) { // 对当前待处理事件进行轮询。
            if (SDL_QUIT == windowEvent.type) { // 如果事件为推出SDL，结束循环。
                cout << "SDL quit!!" << endl;
                break;
            }
        }

    }
    SDL_DestroyWindow(window); // 推出SDL窗体
    SDL_Quit(); // SDL推出
    return 0;
*/
}