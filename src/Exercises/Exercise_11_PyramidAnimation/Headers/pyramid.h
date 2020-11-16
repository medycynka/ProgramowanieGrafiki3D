#ifndef INC_3DGRAPHICSEXAMPLES_PYRAMID_H
#define INC_3DGRAPHICSEXAMPLES_PYRAMID_H

#pragma once

#include "glad/glad.h"
#include <vector>


class Pyramid  {
public:
    Pyramid();
    ~Pyramid() = default;

    void draw() const;

private:
    GLuint vao_{0};
    GLuint buffer_[2] = {0, 0};   // [0] - index buffer, [1] - vertex buffer
    std::vector<GLushort> indices = {
            0, 1, 2, 2, 3, 0, 6, 5, 4, 9, 8, 7, 12, 11, 10, 15, 14, 13
    };
    std::vector<GLfloat> vertices = {
            /* base */
            -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            /* front wall */
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            /* right wall */
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
            /* back wall */
            0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
            /* left wall */
            -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f
    };
};

#endif //INC_3DGRAPHICSEXAMPLES_PYRAMID_H
