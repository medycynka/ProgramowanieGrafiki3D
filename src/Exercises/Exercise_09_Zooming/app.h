//
// Created by pbialas on 05.08.2020.
//


#pragma once

#include <utility>
#include <vector>
#include <glm/matrix.hpp>
#include <memory>

#include "Application/application.h"
#include "Application/utils.h"
#include "glad/glad.h"
#include "camera.h"

class SimpleShapeApplication : public xe::Application {
public:
    SimpleShapeApplication(int width, int height, std::string title, int major = 4, int minor = 1) :
            Application(width, height, std::move(title), major, minor) {}

    ~SimpleShapeApplication() {
            al_.destroy(camera_);
            al_.deallocate(camera_, 1);
    }

    void init() override;

    void frame() override;

    void framebuffer_resize_callback(int w, int h) override;

    void scroll_callback(double xoffset, double yoffset) override;

    Camera* create_camera(){
        auto* new_camera = al_.allocate(1);
        al_.construct(new_camera);

        return new_camera;
    }

    void set_camera(Camera *camera) { camera_ = camera; }

    Camera *camera() { return camera_; }

private:
    std::allocator<Camera> al_{};
    GLuint vao_ = 0;
    GLuint u_pvm_buffer = 0;
    glm::mat4 P_{};
    glm::mat4 M_{};
    glm::mat4 V_{};
    Camera *camera_ = nullptr;
};