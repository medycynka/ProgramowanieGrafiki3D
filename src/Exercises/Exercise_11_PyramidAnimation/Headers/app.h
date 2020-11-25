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
#include "pyramid.h"


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
            p_al_.destroy(pyramid_);
            p_al_.deallocate(pyramid_, 1);
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

    void draw_and_send_pmv(const glm::mat4 &pmv_);

private:
    // Allocators
    std::allocator<Camera> al_{};
    std::allocator<CameraControler> cc_al_{};
    std::allocator<Pyramid> p_al_{};

    // Buffers
    GLuint vao_ = 0;
    GLuint u_pvm_buffer = 0;

    // Matrices
    glm::mat4 PMV_basic{};         // helper pmv matrix for faster (less operations) multiplication
    glm::mat4 M_{};                // singular matrix (can be used as model view matrix)
    glm::mat4 R_{};                // rotation matrix for main pyramid
    glm::mat4 O_{};                // translation matrix (orbital movement) for main pyramid
    glm::mat4 PMV_{};              // pmv matrix for main pyramid
    glm::mat4 R_moon{};            // rotation matrix for main moon pyramid
    glm::mat4 O_moon{};            // translation matrix (orbital movement) for moon pyramid
    glm::mat4 S_moon{};            // scale matrix for moon pyramid
    glm::mat4 PMV_moon{};          // pmv matrix for moon pyramid
    glm::mat4 R_satellite{};       // rotation matrix for main satellite pyramid
    glm::mat4 O_satellite{};       // translation matrix (orbital movement) for satellite pyramid
    glm::mat4 S_satellite{};       // scale matrix for satellite pyramid
    glm::mat4 PMV_satellite{};     // pmv matrix for satellite pyramid

    // Pointers
    Camera *camera_ = nullptr;
    CameraControler *controller_ = nullptr;
    Pyramid* pyramid_ = nullptr;

    // Starting time point
    std::chrono::steady_clock::time_point start_;

    // Spinning axis
    glm::vec3 axis_{0.0f, 1.0f, 0.0f};
    glm::vec3 satellite_axis{0.0f, 0.0f, 1.0f};

    // Constants
    constexpr static const float PI_ = glm::pi<float>();
    constexpr static const float doublePI_ = 2.0f * PI_;
    constexpr static const float rotation_period = 4.0f;
    constexpr static const float rotation_angle = -doublePI_ / rotation_period;
    constexpr static const float orbital_rotation_period = 20.0f;
    constexpr static const float orbital_rotation_angle = doublePI_ / orbital_rotation_period;
    constexpr static const float a = 10.0f;
    constexpr static const float b = 8.0f;
    constexpr static const float r_moon = 3.0f;
    constexpr static const float moon_rotation_period = 10.0f;
    constexpr static const float moon_rotation_angle = -doublePI_ / moon_rotation_period;
    constexpr static const float moon_orbital_rotation_angle = doublePI_ / moon_rotation_period;
    constexpr static const float r_satellite = 1.5f;
    constexpr static const float satellite_rotation_period = 2.0f;
    constexpr static const float satellite_rotation_angle = -doublePI_ / satellite_rotation_period;
    constexpr static const float satellite_orbital_rotation_angle = doublePI_ / satellite_rotation_period;
};