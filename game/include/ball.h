#pragma once
#include <glm.hpp>

class Ball {
public:
    glm::vec3 position;
    glm::vec3 velocity;
    float radius;
    glm::vec3 color;

    Ball();

    void reset();
    void update(float deltaTime);
    bool checkTableCollision(float tableWidth, float tableHeight, float tableDepth);
};
