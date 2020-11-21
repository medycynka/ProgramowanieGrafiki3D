#ifndef INC_3DGRAPHICSEXAMPLES_PYRAMID_H
#define INC_3DGRAPHICSEXAMPLES_PYRAMID_H

#pragma once

#include "glad/glad.h"
#include <vector>
#include <string>
#include <iostream>


class Pyramid  {
public:
    Pyramid();
    ~Pyramid();

    void draw() const;

private:
    GLuint vao_{0};
    GLuint buffer_[2] = {0, 0};   // [0] - index buffer, [1] - vertex buffer
    GLuint diffuse_texture_{0};
    uint8_t *data_ = nullptr;
    std::vector<GLushort> indices = {
            0, 1, 2, 2, 3, 0, 4, 1, 0, 5, 2, 1, 6, 3, 2, 7, 0, 3
    };
    std::vector<GLfloat> vertices = {
            /* base */
            -0.5f, -0.5f, -0.5f, 0.191f, 0.5f,
            0.5f, -0.5f, -0.5f, 0.5f, 0.191f,
            0.5f, -0.5f, 0.5f, 0.809f, 0.5f,
            -0.5f, -0.5f, 0.5f, 0.5f, 0.809f,
            /* top */
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 1.0f
    };
};

#endif //INC_3DGRAPHICSEXAMPLES_PYRAMID_H
