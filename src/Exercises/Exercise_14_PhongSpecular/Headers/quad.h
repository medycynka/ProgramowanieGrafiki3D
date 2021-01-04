#ifndef INC_3DGRAPHICSEXAMPLES_QUAD_H
#define INC_3DGRAPHICSEXAMPLES_QUAD_H

#pragma once

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include "phong_material.h"
#include <memory>

class Quad  {
public:
    Quad();
    ~Quad();

    void draw();

    std::allocator<PhongMaterial>& get_material_allocator(){
        return matAl;
    }

    void set_material(PhongMaterial* new_material){
        material_ = new_material;
    }

    PhongMaterial* get_material(){
        return material_;
    }

private:
    GLuint vao_{0};
    GLuint buffer_[2] = {0, 0};   // [0] - index buffer, [1] - vertex buffer

    std::vector<GLushort> indices = {
            0, 1, 2, 2, 3, 0
    };
    std::vector<GLfloat> vertices = {
            -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f
    };
    std::allocator<PhongMaterial> matAl{};
    PhongMaterial* material_ = nullptr;
};

#endif //INC_3DGRAPHICSEXAMPLES_QUAD_H
