#pragma once
#include <glm.hpp>

class Ball;

class Paddle {
public:
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 color;
    bool isAI;
    float speed;

    Paddle(bool ai = false, glm::vec3 startPos = glm::vec3(0.0f));

    void update(float deltaTime, Ball* ball = nullptr);
    bool checkCollision(Ball& ball);

    void move(float dx, float dz, float tableWidth, float tableDepth);
};
