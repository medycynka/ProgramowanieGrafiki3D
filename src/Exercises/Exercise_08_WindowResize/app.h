//
// Created by pbialas on 05.08.2020.
//


#pragma once

#include <utility>
#include <vector>
#include <glm/matrix.hpp>

#include "Application/application.h"
#include "Application/utils.h"

#include "glad/glad.h"

class SimpleShapeApplication : public xe::Application {
public:
    SimpleShapeApplication(int width, int height, std::string title, int major = 4, int minor = 1) :
            Application(width, height, std::move(title), major, minor) {}

    void init() override;

    void frame() override;

    void framebuffer_resize_callback(int w, int h) override;

private:
    GLuint vao_ = 0;
    GLuint u_pvm_buffer = 0;
    float fov_ = 0;
    float aspect_ = 0;
    float near_ = 0;
    float far_ = 0;
    glm::mat4 P_{};
    glm::mat4 M_{};
    glm::mat4 V_{};
};