#include "Camera.h"
#include <cmath>

Camera::Camera() :
    target(0.0f, 0.0f, 0.0f),
    up(0.0f, 1.0f, 0.0f),
    distance(60.0f),
    angleX(-20.0f),
    angleY(55.0f),
    screenWidth(1096),
    screenHeight(720) {
    updatePosition();
}

void Camera::updatePosition() {
    position.x = target.x + distance * cos(glm::radians(angleY)) * sin(glm::radians(angleX));
    position.y = target.y + distance * sin(glm::radians(angleY));
    position.z = target.z + distance * cos(glm::radians(angleY)) * cos(glm::radians(angleX));
}

void Camera::clampAngles() {
    if (angleY > 85.0f) angleY = 85.0f;
    if (angleY < -10.0f) angleY = -10.0f;
}

void Camera::processMouse(float xoffset, float yoffset) {
    float sensitivity = 0.1f;
    angleX += xoffset * sensitivity;
    angleY -= yoffset * sensitivity;
    clampAngles();
    updatePosition();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(45.0f),
        (float)screenWidth / (float)screenHeight,
        0.1f, 100.0f);
}

void Camera::setScreenSize(unsigned int width, unsigned int height) {
    screenWidth = width;
    screenHeight = height;
}

void Camera::zoom(float yoffset) {
    distance -= yoffset * 2.0f;
    if (distance < 10.0f) distance = 10.0f;
    if (distance > 60.0f) distance = 60.0f;
    updatePosition();
}