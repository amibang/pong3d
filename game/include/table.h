#pragma once
#include <glm.hpp>

class Table {
public:
    glm::vec3 size;
    glm::vec3 color;
    glm::vec3 netColor;

    Table();

    float getWidth() const { return size.x; }
    float getHeight() const { return size.y; }
    float getDepth() const { return size.z; }
};
