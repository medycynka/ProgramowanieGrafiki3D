//
// Created by pbialas on 05.08.2020.
//


#pragma once

#include <utility>
#include <vector>
#include <chrono>
#include <glm/matrix.hpp>

#include "Application/application.h"
#include "Application/utils.h"
#include "glad/glad.h"
#include "camera_controler.h"
#include "quad.h"


class SimpleShapeApplication : public xe::Application {
public:
    SimpleShapeApplication(int width, int height, std::string title, int major = 4, int minor = 1) :
            Application(width, height, std::move(title), major, minor) {

    }

    ~SimpleShapeApplication() {
            al_.destroy(camera_);
            al_.deallocate(camera_, 1);
            cc_al_.destroy(controller_);
            cc_al_.deallocate(controller_, 1);
            q_al_.destroy(quad_);
            q_al_.deallocate(quad_, 1);
    }

    void init() override;

    void frame() override;

    void framebuffer_resize_callback(int w, int h) override;

    void scroll_callback(double xoffset, double yoffset) override;

    void mouse_button_callback(int button, int action, int mods) override;

    void cursor_position_callback(double x, double y) override;

    Camera* create_camera(){
        auto* new_camera = al_.allocate(1);
        al_.construct(new_camera);

        return new_camera;
    }

    void set_camera(Camera *camera) { camera_ = camera; }

    Camera *camera() { return camera_; }

    CameraControler* create_camera_controller(int w, int h){
        auto* new_camera_ctr = cc_al_.allocate(1);
        cc_al_.construct(new_camera_ctr, w, h, camera_);

        return new_camera_ctr;
    }

    void set_controller(CameraControler *controler) { controller_ = controler; }

    CameraControler* controler() { return controller_; }

    void draw_and_send_matrices(const glm::mat4 &p_, const glm::mat4 &mv_, const glm::mat3 &n_);

private:
    // Allocators
    std::allocator<Camera> al_{};
    std::allocator<CameraControler> cc_al_{};
    std::allocator<Quad> q_al_{};

    // Buffers
    GLuint vao_ = 0;
    GLuint u_pvm_buffer = 0;

    // Matrices
    glm::mat4 M_{};
    glm::mat4 P_{};
    glm::mat4 MV_{};
    glm::mat3 N_{};

    // Pointers
    Camera *camera_ = nullptr;
    CameraControler *controller_ = nullptr;
    Quad* quad_ = nullptr;
};