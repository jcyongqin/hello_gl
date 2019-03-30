//
// Created by wyq on 2019/3/30.
//

#include "Controller.h"
#include <cmath>
//========
#include <cstdio>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

Controller::Controller(GLFWwindow *pWindow) : window(pWindow) {
    lastTime = glfwGetTime();
    deltaTime = 0.0;
    glfwGetCursorPos(window, &xPos, &yPos);
    cameraPos = glm::vec3(-3.0f, 3.0f, -3.0f);
    direction = glm::vec3(
            cosf(verticalAngle) * sinf(horizontalAngle),
            sinf(verticalAngle),
            cosf(verticalAngle) * cosf(horizontalAngle)
    );
}

void Controller::update() {
    double currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
}

glm::mat4 Controller::getViewMatrix() {
    // mouse position
    double cXPos, cYPos;
    glfwGetCursorPos(window, &cXPos, &cYPos);

    // if R Button down, Compute new orientation
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)) {
        horizontalAngle -= mouseSpeed * deltaTime * (cXPos - xPos);
        verticalAngle -= mouseSpeed * deltaTime * (cYPos - yPos);
    }

    xPos = cXPos;
    yPos = cYPos;

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    glm::vec3 direction(
            cosf(verticalAngle) * sinf(horizontalAngle),
            sinf(verticalAngle),
            cosf(verticalAngle) * cosf(horizontalAngle)
    );

    // Right vector
    glm::vec3 right = glm::vec3(
            sin(horizontalAngle - 3.14f / 2.0f),
            0,
            cos(horizontalAngle - 3.14f / 2.0f)
    );

    // Up vector : perpendicular to both direction and right
    glm::vec3 up = glm::cross(right, direction);


    // Move forward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += direction * deltaTime * moveSpeed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= direction * deltaTime * moveSpeed;
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += right * deltaTime * moveSpeed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= right * deltaTime * moveSpeed;
    }
    // Strafe up
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        cameraPos += up * deltaTime * moveSpeed;
    }
    // Strafe down
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        cameraPos -= up * deltaTime * moveSpeed;
    }

    glm::mat4 ViewMatrix = glm::lookAt(
            cameraPos,           // Camera is here
            cameraPos + direction, // and looks here : at the same position, plus "direction"
            up             // Head is up (set to 0,-1,0 to look upside-down)
    );
    return ViewMatrix;
}


