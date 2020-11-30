#ifndef INC_3DGRAPHICSEXAMPLES_QUAD_H
#define INC_3DGRAPHICSEXAMPLES_QUAD_H

#pragma once

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>


class Quad  {
public:
    Quad();
    ~Quad();

    void draw();

private:
    GLuint vao_{0};
    GLuint buffer_[2] = {0, 0};   // [0] - index buffer, [1] - vertex buffer
    GLuint diffuse_texture_{0};

    uint8_t *data_ = nullptr;
    std::vector<GLushort> indices = {
            0, 1, 2, 2, 3, 0
    };
    std::vector<GLfloat> vertices = {
            -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f
    };
};

#endif //INC_3DGRAPHICSEXAMPLES_QUAD_H
