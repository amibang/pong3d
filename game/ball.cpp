#include "Ball.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

Ball::Ball() : radius(0.5f), color(1.0f, 0.5f, 0.0f) {
    reset();
}

void Ball::reset() {
    position = glm::vec3(0.0f, radius, 0.0f);

    srand(static_cast<unsigned>(time(nullptr)));
    float angle = (rand() % 360) * 3.14159f / 180.0f;
    float speed = 10.0f;
    velocity = glm::vec3(cos(angle) * speed, 0.0f, sin(angle) * speed);
}

void Ball::update(float deltaTime) {
    position += velocity * deltaTime;
    velocity.y -= 9.8f * deltaTime;

    if (position.y < radius) {
        position.y = radius;
        velocity.y = -velocity.y * 0.8f;
    }
}

bool Ball::checkTableCollision(float tableWidth, float tableHeight, float tableDepth) {
    return (position.x < -tableWidth / 2 || position.x > tableWidth / 2);
}