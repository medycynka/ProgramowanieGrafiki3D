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

    void calculate_solar_system_pmv(float elapsed_time);

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
    glm::mat4 M_{};                // singular matrix (can be used as model view matrix)
    glm::mat4 PMV_basic{};         // helper pmv matrix for faster (less operations) multiplication
    glm::mat4 PMV_earth_basic{};   // helper pmv matrix for faster (less operations) multiplication
    glm::mat4 R_sun{};             // rotation matrix for sun pyramid
    glm::mat4 O_sun{};             // translation matrix (orbital movement) for sun pyramid
    glm::mat4 S_sun{};             // scale matrix for sun pyramid
    glm::mat4 PMV_sun{};           // pmv matrix for sun pyramid
    glm::mat4 R_mercury{};         // rotation matrix for mercury pyramid
    glm::mat4 O_mercury{};         // translation matrix (orbital movement) for mercury pyramid
    glm::mat4 S_mercury{};         // scale matrix for mercury pyramid
    glm::mat4 PMV_mercury{};       // pmv matrix for mercury pyramid
    glm::mat4 R_venus{};           // rotation matrix for venus pyramid
    glm::mat4 O_venus{};           // translation matrix (orbital movement) for venus pyramid
    glm::mat4 S_venus{};           // scale matrix for venus pyramid
    glm::mat4 PMV_venus{};         // pmv matrix for venus pyramid
    glm::mat4 R_earth{};           // rotation matrix for main pyramid
    glm::mat4 O_earth{};           // translation matrix (orbital movement) for main pyramid
    glm::mat4 PMV_earth{};         // pmv matrix for main pyramid
    glm::mat4 R_moon{};            // rotation matrix for main moon pyramid
    glm::mat4 O_moon{};            // translation matrix (orbital movement) for moon pyramid
    glm::mat4 S_moon{};            // scale matrix for moon pyramid
    glm::mat4 PMV_moon{};          // pmv matrix for moon pyramid
    glm::mat4 R_satellite{};       // rotation matrix for main satellite pyramid
    glm::mat4 O_satellite{};       // translation matrix (orbital movement) for satellite pyramid
    glm::mat4 S_satellite{};       // scale matrix for sun pyramid
    glm::mat4 PMV_satellite{};     // pmv matrix for satellite pyramid
    glm::mat4 R_mars{};            // rotation matrix for mars pyramid
    glm::mat4 O_mars{};            // translation matrix (orbital movement) for mars pyramid
    glm::mat4 S_mars{};            // scale matrix for mars pyramid
    glm::mat4 PMV_mars{};          // pmv matrix for mars pyramid
    glm::mat4 R_phobos{};          // rotation matrix for phobos pyramid
    glm::mat4 O_phobos{};          // translation matrix (orbital movement) for phobos pyramid
    glm::mat4 S_phobos{};          // scale matrix for phobos pyramid
    glm::mat4 PMV_phobos{};        // pmv matrix for phobos pyramid
    glm::mat4 R_deimos{};          // rotation matrix for deimos pyramid
    glm::mat4 O_deimos{};          // translation matrix (orbital movement) for deimos pyramid
    glm::mat4 S_deimos{};          // scale matrix for deimos pyramid
    glm::mat4 PMV_deimos{};        // pmv matrix for deimos pyramid

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
    //Sun
    constexpr static const float r_sun = 0.05f;
    constexpr static const float sun_rotation_period = 21.0f;
    constexpr static const float sun_orbital_rotation_period = 250.0f;
    // Mercury
    constexpr static const float mercury_rotation_period = 234.58f;
    constexpr static const float mercury_orbital_rotation_period = 83.04f;
    constexpr static const float mercury_a = 6.0f;
    constexpr static const float mercury_b = 4.8f;
    // Venus
    constexpr static const float venus_rotation_period = 109.29f;
    constexpr static const float venus_orbital_rotation_period = 32.52f;
    constexpr static const float venus_a = 8.4f;
    constexpr static const float venus_b = 10.5f;
    // Earth
    constexpr static const float rotation_period = 4.0f;
    constexpr static const float orbital_rotation_period = 20.0f;
    constexpr static const float earth_a = 15.0f;
    constexpr static const float earth_b = 12.0f;
    // Moon
    constexpr static const float moon_rotation_period = 109.6f;
    constexpr static const float moon_orbital_rotation_period = 109.6f;
    constexpr static const float r_moon = 3.0f;
    // Satellite
    constexpr static const float satellite_rotation_period = 2.0f;
    constexpr static const float r_satellite = 1.5f;
    // Mars
    constexpr static const float mars_rotation_period = 4.104f;
    constexpr static const float mars_orbital_rotation_period = 37.63f;
    constexpr static const float mars_a = 22.86f;
    constexpr static const float mars_b = 18.29f;
    // Phobos
    constexpr static const float phobos_rotation_period = 1.0f;
    constexpr static const float phobos_orbital_rotation_period = 1.0f;
    constexpr static const float phobos_r = 1.25;
    // Deimos
    constexpr static const float deimos_rotation_period = 6.0f;
    constexpr static const float deimos_orbital_rotation_period = 4.0f;
    constexpr static const float deimos_r = 2;
};