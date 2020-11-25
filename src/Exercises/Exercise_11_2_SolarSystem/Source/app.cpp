//
// Created by pbialas on 25.09.2020.
//

#include "../Headers/app.h"

#include <iostream>
#include <tuple>
#include <glm/gtx/transform.hpp>

#include "Application/utils.h"


void SimpleShapeApplication::init() {
    auto program = xe::create_program(std::string(PROJECT_DIR) + "/shaders/base_vs.glsl", std::string(PROJECT_DIR) + "/shaders/base_fs.glsl");

    if (!program) {
        std::cerr << "Cannot create program from " << std::string(PROJECT_DIR) + "/shaders/base_vs.glsl" << " and ";
        std::cerr << std::string(PROJECT_DIR) + "/shaders/base_fs.glsl" << " shader files" << "\n";
    }

    // uniform blocks
    auto u_matrix_index = glGetUniformBlockIndex(program, "Matrices");
    if (u_matrix_index == GL_INVALID_INDEX) {
        std::cout << "Cannot find Matrices uniform block in program" << "\n";
    } else {
        glUniformBlockBinding(program, u_matrix_index, 0);
    }

    // Camera starting position for scaling, zooming and moving
    glm::vec3 cameraPos = {0.0f, 45.0f,  0.1f};
    glm::vec3 cameraCenter = {0.0f, 0.0f, 0.0f};
    glm::vec3 cameraUp = {0.0f, 1.0f, 0.0f};

    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);
    int w, h;
    std::tie(w, h) = frame_buffer_size();

    // Creating pyramid, camera and camera controller pointers and initializing them
    pyramid_ = p_al_.allocate(1);
    p_al_.construct(pyramid_);
    if(!pyramid_){
        std::cerr << "Couldn't create pyramid pointer." << "\n";
    }

    camera_ = create_camera();
    if(!camera_){
        std::cerr << "Couldn't create camera pointer." << "\n";
    }

    controller_ = create_camera_controller(w, h);
    if(!controller_){
        std::cerr << "Couldn't create camera controller pointer." << "\n";
    }

    camera_->perspective(glm::pi<float>()/4.0, (float)w / (float)h, 0.1f, 100.0f);
    camera_->look_at(cameraPos, cameraCenter, cameraUp);

    M_ = glm::mat4(1.0f);
    S_sun = glm::scale(glm::vec3(5.0f, 5.0f, 5.0f));
    S_mercury = glm::scale(glm::vec3(0.4f, 0.4f, 0.4f));
    S_venus = glm::scale(glm::vec3(0.95f, 0.95f, 0.95f));
    S_moon = glm::scale(glm::vec3(0.27f, 0.27f, 0.25f));
    S_satellite = glm::scale(glm::vec3(0.1f, 0.1f, 0.1f));
    S_mars = glm::scale(glm::vec3(0.52f, 0.52f, 0.52f));
    S_phobos = glm::scale(glm::vec3(0.1f, 0.1f, 0.1f));
    S_deimos = glm::scale(glm::vec3(0.2f, 0.2f, 0.2f));
    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glUseProgram(program);

    start_ = std::chrono::steady_clock::now();
}

void SimpleShapeApplication::frame() {
    auto now = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<float>>(now - start_).count();

    // Calculating extended pmv matrices for every pyramid
    calculate_solar_system_pmv(elapsed_time);

    // Drawing pyramids and sending pmv matrix to the shader
    draw_and_send_pmv(PMV_sun);
    draw_and_send_pmv(PMV_mercury);
    draw_and_send_pmv(PMV_venus);
    draw_and_send_pmv(PMV_earth);
    draw_and_send_pmv(PMV_moon);
    draw_and_send_pmv(PMV_satellite);
    draw_and_send_pmv(PMV_mars);
    draw_and_send_pmv(PMV_phobos);
    draw_and_send_pmv(PMV_deimos);
}

void SimpleShapeApplication::framebuffer_resize_callback(int w, int h) {
    Application::framebuffer_resize_callback(w, h);
    glViewport(0, 0, w, h);
    camera_->set_aspect((float) w / (float)h);
    controller_->update_scale(w, h);
}

void SimpleShapeApplication::scroll_callback(double xoffset, double yoffset) {
    Application::scroll_callback(xoffset, yoffset);
    camera()->zoom((float)yoffset / 30.0f);
}

void SimpleShapeApplication::mouse_button_callback(int button, int action, int mods) {
    Application::mouse_button_callback(button, action, mods);

    if(controller_){
        double x;
        double y;

        glfwGetCursorPos(window_, &x, &y);

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            controller_->LMB_pressed((float)x, (float)y);
        }

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
            controller_->LMB_released((float)x, (float)y);
        }
    }
}

void SimpleShapeApplication::cursor_position_callback(double x, double y) {
    Application::cursor_position_callback(x, y);

    if(controller_){
        controller_->mouse_moved((float)x, (float)y);
    }
}

void SimpleShapeApplication::calculate_solar_system_pmv(float elapsed_time) {
    PMV_basic = camera_->projection() * M_ * camera_->view();

    // Sun
    R_sun = glm::rotate(M_, sun_rotation_angle * elapsed_time, axis_);
    O_sun = glm::translate(M_, {r_sun * std::cos(sun_orbital_rotation_angle * elapsed_time), 0.0f, r_sun * std::sin(sun_orbital_rotation_angle * elapsed_time)});
    PMV_sun = PMV_basic * O_sun * R_sun * S_sun;

    // Mercury
    R_mercury = glm::rotate(M_, mercury_rotation_angle * elapsed_time, axis_);
    O_mercury = glm::translate(M_, {mercury_a * std::cos(mercury_orbital_rotation_angle * elapsed_time), 0.0f, mercury_b * std::sin(mercury_orbital_rotation_angle * elapsed_time)});
    PMV_mercury = PMV_basic * O_mercury * R_mercury * S_mercury;

    // Venus
    R_venus = glm::rotate(M_, venus_rotation_angle * elapsed_time, axis_);
    O_venus = glm::translate(M_, {venus_a * std::cos(venus_orbital_rotation_angle * elapsed_time), 0.0f, venus_b * std::sin(venus_orbital_rotation_angle * elapsed_time)});
    PMV_venus = PMV_basic * O_venus * R_venus * S_venus;

    // Earth
    R_earth = glm::rotate(M_, rotation_angle * elapsed_time, axis_);
    O_earth = glm::translate(M_, {earth_a * std::cos(orbital_rotation_angle * elapsed_time), 0.0f, earth_b * std::sin(orbital_rotation_angle * elapsed_time)});
    PMV_earth_basic = PMV_basic * O_earth;
    PMV_earth = PMV_earth_basic * R_earth;

    // Moon
    R_moon = glm::rotate(M_, moon_rotation_angle * elapsed_time, axis_);
    O_moon = glm::translate(M_, {r_moon * std::cos(moon_orbital_rotation_angle * elapsed_time), 0.0f, r_moon * std::sin(moon_orbital_rotation_angle * elapsed_time)});
    PMV_moon = PMV_earth_basic * O_moon * R_moon * S_moon;

    // Satellite
    R_satellite = glm::rotate(M_, satellite_rotation_angle * elapsed_time, satellite_axis);
    O_satellite = glm::translate(M_, {r_satellite * std::cos(satellite_orbital_rotation_angle * elapsed_time), r_satellite * std::sin(satellite_orbital_rotation_angle * elapsed_time), 0.0f});
    PMV_satellite = PMV_earth_basic * O_satellite * R_satellite * S_satellite;

    // Mars
    R_mars = glm::rotate(M_, mars_rotation_angle * elapsed_time, axis_);
    O_mars = glm::translate(M_, {mars_a * std::cos(mars_orbital_rotation_angle * elapsed_time), 0.0f, mars_b * std::sin(mars_orbital_rotation_angle * elapsed_time)});
    PMV_mars = PMV_basic * O_mars * R_mars * S_mars;

    // Phobos
    R_phobos = glm::rotate(M_, phobos_rotation_angle * elapsed_time, axis_);
    O_phobos = glm::translate(M_, {phobos_r * std::cos(phobos_orbital_rotation_angle * elapsed_time), 0.0f, phobos_r * std::sin(phobos_orbital_rotation_angle * elapsed_time)});
    PMV_phobos = PMV_basic * O_mars * O_phobos * R_phobos * S_phobos;

    // Deimos
    R_deimos = glm::rotate(M_, deimos_rotation_angle * elapsed_time, axis_);
    O_deimos = glm::translate(M_, {deimos_r * std::cos(deimos_orbital_rotation_angle * elapsed_time), 0.0f, deimos_r * std::sin(deimos_orbital_rotation_angle * elapsed_time)});
    PMV_deimos = PMV_basic * O_mars * O_deimos * R_deimos * S_deimos;
}

void SimpleShapeApplication::draw_and_send_pmv(const glm::mat4 &pmv_) {
    pyramid_->draw();

    // sending updated pvm matrix to shader
    glGenBuffers(1, &u_pvm_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, u_pvm_buffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &pmv_[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, u_pvm_buffer);
}