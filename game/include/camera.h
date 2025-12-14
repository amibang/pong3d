#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera {
public:
    Camera();

    void updatePosition();
    void processMouse(float xoffset, float yoffset);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix() const;

    void setScreenSize(unsigned int width, unsigned int height);
    void zoom(float yoffset);

private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    float distance;
    float angleX;
    float angleY;
    unsigned int screenWidth;
    unsigned int screenHeight;

    void clampAngles();
};