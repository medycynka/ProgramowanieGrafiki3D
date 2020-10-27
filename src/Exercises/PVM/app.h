//
// Created by pbialas on 05.08.2020.
//


#pragma once

#include <utility>
#include <vector>


#include "Application/application.h"
#include "Application/utils.h"

#include "glad/glad.h"

class SimpleShapeApplication : public xe::Application {
public:
    SimpleShapeApplication(int width, int height, std::string title, int major = 4, int minor = 1) :
            Application(width, height, std::move(title), major, minor), w_{width}, h_{height} {}

    void init() override;;

    void frame() override;

private:
    GLuint vao_ = 0;
    int w_;
    int h_;
};