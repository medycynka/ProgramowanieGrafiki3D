//
// Created by pbialas on 25.09.2020.
//

#include "Exercises/Exercise_11_PyramidAnimation/Headers/app.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Application/utils.h"


void SimpleShapeApplication::init() {
    auto program = xe::create_program(std::string(PROJECT_DIR) + "/shaders/base_vs.glsl", std::string(PROJECT_DIR) + "/shaders/base_fs.glsl");

    if (!program) {
        std::cerr << "Cannot create program from " << std::string(PROJECT_DIR) + "/shaders/base_vs.glsl" << " and ";
        std::cerr << std::string(PROJECT_DIR) + "/shaders/base_fs.glsl" << " shader files" << std::endl;
    }

    // Create a pyramid pointer
    pyramid_ = p_al_.allocate(1);
    p_al_.construct(pyramid_);

    // uniform blocks
    auto u_matrix_index = glGetUniformBlockIndex(program, "Matrices");
    if (u_matrix_index == GL_INVALID_INDEX) {
        std::cout << "Cannot find Matrices uniform block in program" << "\n";
    } else {
        glUniformBlockBinding(program, u_matrix_index, 0);
    }

    // Camera starting position for scaling, zooming and moving
    glm::vec3 cameraPos = {0.0f, 30.0f,  0.1f};
    glm::vec3 cameraCenter = {0.0f, 0.0f, 0.0f};
    glm::vec3 cameraUp = {0.0f, 1.0f, 0.0f};

    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);
    int w, h;
    std::tie(w, h) = frame_buffer_size();

    camera_ = create_camera();
    controler_ = create_camera_controler(w, h);
    camera_->perspective(glm::pi<float>()/4.0, (float)w / (float)h, 0.1f, 100.0f);
    camera_->look_at(cameraPos, cameraCenter, cameraUp);
    M_ = glm::mat4(1.0f);
    S_moon = glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
    S_satellite = glm::scale(glm::vec3(0.25f, 0.25f, 0.25f));
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

    // Calculate pyramids rotations
    auto rotation_angle = 2.0f * glm::pi<float>() * elapsed_time / moon_rotation_period;
    auto orbital_rotation_angle = 2.0f * glm::pi<float>() * elapsed_time / moon_rotation_period;
    R_moon = glm::rotate(glm::mat4(1.0f), rotation_angle, axis_);
    O_moon = glm::translate(glm::mat4(1.0f), {r_moon * cos(orbital_rotation_angle), 0.0f, r_moon * sin(orbital_rotation_angle)});

    rotation_angle = 2.0f * glm::pi<float>() * elapsed_time / 0.5f;
    orbital_rotation_angle = 2.0f * glm::pi<float>() * elapsed_time / satellite_rotation_period;
    R_satellite = glm::rotate(glm::mat4(1.0f), rotation_angle, satellite_axis);
    O_satellite = glm::translate(glm::mat4(1.0f), {r_satellite * cos(orbital_rotation_angle), r_satellite * sin(orbital_rotation_angle), 0.0f});

    rotation_angle = 2.0f * glm::pi<float>() * elapsed_time / rotation_period;
    orbital_rotation_angle = 2.0f * glm::pi<float>() * elapsed_time / orbital_rotation_period;
    R_ = glm::rotate(glm::mat4(1.0f), rotation_angle, axis_);
    O_ = glm::translate(glm::mat4(1.0f), {a * cos(orbital_rotation_angle), 0.0f, b * sin(orbital_rotation_angle)});


    pyramid_->draw();
    // sending updated pvm matrix to shader
    PMV_moon = camera_->projection() * M_ * camera_->view() * O_ * O_moon * R_ * S_moon;
    glGenBuffers(1, &u_pvm_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, u_pvm_buffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &PMV_moon[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, u_pvm_buffer);


    pyramid_->draw();
    // sending updated pvm matrix to shader
    PMV_satellite = camera_->projection() * M_ * camera_->view() * O_ * O_satellite * R_satellite * S_satellite;
    glGenBuffers(1, &u_pvm_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, u_pvm_buffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &PMV_satellite[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, u_pvm_buffer);


    pyramid_->draw();
    // sending updated pvm matrix to shader
    PMV_ = camera_->projection() * M_ * camera_->view() * O_ * R_;
    glGenBuffers(1, &u_pvm_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, u_pvm_buffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &PMV_[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, u_pvm_buffer);
}

void SimpleShapeApplication::framebuffer_resize_callback(int w, int h) {
    Application::framebuffer_resize_callback(w, h);
    glViewport(0, 0, w, h);
    camera_->set_aspect((float) w / (float)h);
    controler_->update_scale(w, h);
}

void SimpleShapeApplication::scroll_callback(double xoffset, double yoffset) {
    Application::scroll_callback(xoffset, yoffset);
    camera()->zoom((float)yoffset / 30.0f);
}

void SimpleShapeApplication::mouse_button_callback(int button, int action, int mods) {
    Application::mouse_button_callback(button, action, mods);

    if(controler_){
        double x;
        double y;

        glfwGetCursorPos(window_, &x, &y);

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            controler_->LMB_pressed((float)x, (float)y);
        }

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
            controler_->LMB_released((float)x, (float)y);
        }
    }
}

void SimpleShapeApplication::cursor_position_callback(double x, double y) {
    Application::cursor_position_callback(x, y);

    if(controler_){
        controler_->mouse_moved((float)x, (float)y);
    }
}
