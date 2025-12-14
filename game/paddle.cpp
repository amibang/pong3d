#include "Paddle.h"
#include "Ball.h"
#include <algorithm>

Paddle::Paddle(bool ai, glm::vec3 startPos)
    : size(1.0f, 2.0f, 4.0f),
    color(0.882f, 0.137f, 0.282f),
    isAI(ai),
    speed(15.0f) {
    position = startPos;
}

void Paddle::update(float deltaTime, Ball* ball) {
    if (isAI && ball) {
        float targetZ = ball->position.z;
        if (position.z < targetZ - 0.5f) {
            position.z += speed * 0.7f * deltaTime;
        }
        else if (position.z > targetZ + 0.5f) {
            position.z -= speed * 0.7f * deltaTime;
        }
    }
}

bool Paddle::checkCollision(Ball& ball) {
    glm::vec3 closestPoint;
    closestPoint.x = std::max(position.x - size.x / 2, std::min(ball.position.x, position.x + size.x / 2));
    closestPoint.y = std::max(position.y - size.y / 2, std::min(ball.position.y, position.y + size.y / 2));
    closestPoint.z = std::max(position.z - size.z / 2, std::min(ball.position.z, position.z + size.z / 2));

    float dx = closestPoint.x - ball.position.x;
    float dy = closestPoint.y - ball.position.y;
    float dz = closestPoint.z - ball.position.z;
    float distance = sqrt(dx * dx + dy * dy + dz * dz);

    return distance < ball.radius;
}

void Paddle::move(float dx, float dz, float tableWidth, float tableDepth) {
    position.x += dx;
    position.z += dz;

    position.z = std::clamp(position.z,
        -tableDepth / 2 + size.z / 2,
        tableDepth / 2 - size.z / 2);
    position.x = std::clamp(position.x,
        -tableWidth / 2 + size.x / 2,
        0.0f - size.x / 2);
}