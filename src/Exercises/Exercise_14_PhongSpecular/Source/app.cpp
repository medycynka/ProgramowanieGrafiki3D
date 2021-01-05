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
    xe::utils::set_uniform_block_binding(program, "Transformations", 0);
    xe::utils::set_uniform_block_binding(program, "Light", 1);
    xe::utils::set_uniform_block_binding(program, "Material", 2);

    glGenBuffers(1, &u_pvm_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, u_pvm_buffer);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4) + 3 * sizeof(glm::vec4), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, u_pvm_buffer);

    glGenBuffers(1, &u_light_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, u_light_buffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Light), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, u_light_buffer);

    glGenBuffers(1, &u_material_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, u_material_buffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(PhongMaterial), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 2, u_material_buffer);

    // Light
    light_.position = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    light_.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    light_.a = glm::vec4(1.0f, 0.0f, 1.0f, 0.0f);
    light_.ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);

    // Camera starting position for scaling, zooming and moving
    glm::vec3 cameraPos = {0.0f, 4.0f,  0.0f};
    glm::vec3 cameraCenter = {0.0f, 0.0f, 0.0f};
    glm::vec3 cameraUp = {0.1f, 1.0f, 0.0f};

    glClearColor(0.81f, 0.81f, 0.81f, 1.0f);
    int w, h;
    std::tie(w, h) = frame_buffer_size();

    // Creating Quad and PhongMaterial
    quad_ = q_al_.allocate(1);
    q_al_.construct(quad_);
    if(!quad_){
        std::cerr << "Couldn't create quad pointer." << "\n";
    }

    // Loading texture for quad
    glGenTextures(1, &diffuse_texture_);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuse_texture_);
    xe::utils::load_texture(std::string(PROJECT_DIR) + "/Textures/plastic.png");
    glBindTexture(GL_TEXTURE_2D, 0);

    //glGenTextures(1, &shininess_texture_);
    //glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, shininess_texture_);
    xe::utils::load_texture(std::string(PROJECT_DIR) + "/Textures/shininess.png");
    glBindTexture(GL_TEXTURE_2D, 0);

    auto mat_ = quad_->get_material_allocator().allocate(1);
    quad_->get_material_allocator().construct(mat_);
    mat_->Kd = glm::vec3(1.0, 1.0, 1.0);
    mat_->Kd_map = diffuse_texture_;
    mat_->Ks = glm::vec3(0.05, 0.05, 0.05);
    mat_->Ks_map = 0;
    mat_->Ns = 1000.0f;
    mat_->Ns_map = shininess_texture_;
    quad_->set_material(mat_);

    // Creating camera and camera controller pointers and initializing them
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
    xe::utils::set_uniform1i(program, "diffuse_map", 3);
    //xe::utils::set_uniform1i(program,"specular_map",4);
    xe::utils::set_uniform1i(program,"shininess_map",5);
}

void SimpleShapeApplication::frame() {
    P_ = camera_->projection();
    MV_ = M_ * camera_->view();
    N_ = glm::transpose(glm::inverse(glm::mat3(MV_)));
    light_.position_in_vs = MV_ * light_.position;

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
    // sending updated light to shader
    glBindBuffer(GL_UNIFORM_BUFFER, u_light_buffer);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, 4 * sizeof(glm::vec4), &light_.position_in_vs[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBuffer(GL_UNIFORM_BUFFER, u_material_buffer);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(PhongMaterial), quad_->get_material());
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    if(quad_->get_material()->Kd_map > 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, quad_->get_material()->Kd_map);
    }
    if(quad_->get_material()->Ks_map > 0) {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, quad_->get_material()->Ks_map);
    }
    if(quad_->get_material()->Ns_map > 0) {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, quad_->get_material()->Ns_map);
    }
    quad_->draw();

    // sending updated pvm matrix to shader
    glBindBuffer(GL_UNIFORM_BUFFER, u_pvm_buffer);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &p_[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &mv_[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::vec4), &n_[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4) + sizeof(glm::vec4), sizeof(glm::vec3), &n_[1]);
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4) + 2 * sizeof(glm::vec4), sizeof(glm::vec3), &n_[2]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
