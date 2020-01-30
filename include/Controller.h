//
// Created by wyq on 2019/3/30.
//

#ifndef HELLO_GL_CONTROLLER_H
#define HELLO_GL_CONTROLLER_H

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

class Controller {
public:
    Controller(GLFWwindow *pWindow);

    void update();

    glm::mat4 getViewMatrix();


private:
    GLFWwindow *window;
    double lastTime;
    float deltaTime;
    double xPos, yPos;
    float horizontalAngle = 0.83f;
    float verticalAngle = -0.6f;
    float mouseSpeed = 0.0005f;
    float moveSpeed = 0.003f;
    glm::vec3 cameraPos;
    glm::vec3 direction;
};


#endif //{}HELLO_{}GL_CONTROLLER_H
