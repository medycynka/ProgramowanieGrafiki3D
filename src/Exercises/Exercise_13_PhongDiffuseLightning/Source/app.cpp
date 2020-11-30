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
    auto u_matrix_index = glGetUniformBlockIndex(program, "Transformations");
    if (u_matrix_index == GL_INVALID_INDEX) {
        std::cout << "Cannot find Matrices uniform block in program" << "\n";
    } else {
        glUniformBlockBinding(program, u_matrix_index, 0);
    }

    // Camera starting position for scaling, zooming and moving
    glm::vec3 cameraPos = {0.0f, 4.0f,  0.001f};
    glm::vec3 cameraCenter = {0.0f, 0.0f, 0.0f};
    glm::vec3 cameraUp = {0.0f, 1.0f, 0.0f};

    glClearColor(0.81f, 0.81f, 0.81f, 1.0f);
    int w, h;
    std::tie(w, h) = frame_buffer_size();

    // Creating pyramid, camera and camera controller pointers and initializing them
    quad_ = q_al_.allocate(1);
    q_al_.construct(quad_, program);
    if(!quad_){
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
    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glUseProgram(program);

    // Textures
    auto u_diffuse_map_location = glGetUniformLocation(program, "diffuse_map");
    if(u_diffuse_map_location == -1) {
        std::cerr << "Cannot find uniform diffuse_map" << "\n";
    } else {
        glUniform1ui(u_diffuse_map_location, 1);
    }
}

void SimpleShapeApplication::frame() {
    P_ = camera_->projection();
    MV_ = M_ * camera_->view();
    N_ = glm::transpose(glm::inverse(glm::mat3(MV_)));

    draw_and_send_matrices(P_, MV_, N_);
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

void SimpleShapeApplication::draw_and_send_matrices(const glm::mat4 &p_, const glm::mat4 &mv_, const glm::mat3 &n_) {
    quad_->update_light_position(mv_);
    quad_->draw();

    // sending updated pvm matrix to shader
    glGenBuffers(1, &u_pvm_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, u_pvm_buffer);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4) + sizeof(glm::mat3), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &p_[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &mv_[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::mat3), &n_[0]);
    /*glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::vec3), &n_[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4) + sizeof(glm::vec3), sizeof(glm::vec3), &n_[1]);
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4) + 2 * sizeof(glm::vec3), sizeof(glm::vec3), &n_[2]);*/
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, u_pvm_buffer);
}
