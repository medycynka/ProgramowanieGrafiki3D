//
// Created by pbialas on 25.09.2020.
//

#include "app.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Application/utils.h"

void SimpleShapeApplication::init() {


    auto program = xe::create_program(std::string(PROJECT_DIR) + "/shaders/base_vs.glsl", std::string(PROJECT_DIR) + "/shaders/base_fs.glsl");

    if (!program) {
        std::cerr << "Cannot create program from " << std::string(PROJECT_DIR) + "/shaders/base_vs.glsl" << " and ";
        std::cerr << std::string(PROJECT_DIR) + "/shaders/base_fs.glsl" << " shader files" << std::endl;
    }

    std::vector<GLushort> indices = {
            0, 1, 2, 3, 1, 0, 3, 4, 1, /* first house */
            5, 6, 7, 8, 6, 5, 8, 9, 6, /* second house */
            10, 11, 12, 13, 10, 12, /* first house door */
            14, 15, 16, 17, 14, 16, /* second house door */
            18, 19, 20, 21, 18, 20, /* first house window */
            22, 23, 24, 25, 22, 24 /* second house window */
    };
    std::vector<GLfloat> vertices = {
            -0.8f, 0.5f, 0.0f, /* first vertex */ 0.9f, 0.3f, 0.0f, /* color */
            -0.1f, 0.5f, 0.0f, /* second vertex */ 0.2f, 0.7f, 0.1f,
            -0.45f, 0.8f, 0.0f, /* third vertex */ 0.2f, 0.0f, 0.9f,
            -0.8f, -0.5f, 0.0f, 0.63f, 0.45f, 0.41f,
            -0.1f, -0.5f, 0.0f, 0.63f, 0.45f, 0.41f,
            0.1f, 0.5f, 0.0f, /* second house */ 0.05f, 0.47f, 0.06f,
            0.8f, 0.5f, 0.0f, 0.05f, 0.47f, 0.06f,
            0.45f, 0.8f, 0.0f, 0.05f, 0.47f, 0.06f,
            0.1f, -0.5f, 0.0f, 0.54f, 0.8f, 0.89f,
            0.8f, -0.5f, 0.0f, 0.54f, 0.8f, 0.89f,
            /* doors */
            -0.4f, -0.5f, -0.1f, 0.53f, 0.23f, 0.0f,
            -0.2f, -0.5f, -0.1f, 0.43f, 0.16f, 0.0f,
            -0.2f, -0.05f, -0.1f, 0.43f, 0.16f, 0.0f,
            -0.4f, -0.05f, -0.1f, 0.64f, 0.33f, 0.13f,
            0.5, -0.5f, -0.2f, 0.53f, 0.23f, 0.0f,
            0.7f, -0.5f, -0.1f, 0.43f, 0.16f, 0.0f,
            0.7f, -0.05f, -0.1f, 0.43f, 0.16f, 0.0f,
            0.5f, -0.05f, -0.1f, 0.64f, 0.33f, 0.13f,
            /* windows */
            -0.7f, -0.15f, -0.1f, 0.0f, 0.43f, 1.0f,
            -0.5f, -0.15f, -0.1f, 0.0f, 0.23f, 0.53f,
            -0.5f, 0.15f, -0.1f, 0.09f, 0.35f, 0.68f,
            -0.7f, 0.15f, -0.1f, 0.27f, 0.59f, 1.0f,
            0.2f, -0.15f, -0.1f, 0.0f, 0.43f, 1.0f,
            0.4f, -0.15f, -0.1f, 0.0f, 0.23f, 0.53f,
            0.4f, 0.15f, -0.1f, 0.09f, 0.35f, 0.68f,
            0.2f, 0.15f, -0.1f, 0.27f, 0.59f, 1.0f
    };

    auto u_modifiers_index = glGetUniformBlockIndex(program, "Modifiers");
    if (u_modifiers_index == GL_INVALID_INDEX) {
        std::cout << "Cannot find Modifiers uniform block in program" << "\n";
    } else {
        glUniformBlockBinding(program, u_modifiers_index, 0);
    }

    GLuint idx_buffer_handle;
    glGenBuffers(1, &idx_buffer_handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx_buffer_handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLuint v_buffer_handle;
    glGenBuffers(1, &v_buffer_handle);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx_buffer_handle);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint ubo_handle(0u);
    glGenBuffers(1, &ubo_handle);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_handle);
    glBufferData(GL_UNIFORM_BUFFER, 5 * sizeof(GLfloat), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo_handle);
    GLfloat intensity = 1.0f;
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_handle);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(GLfloat), &intensity);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glm::vec3 light_color = {1.0f, 1.0f, 1.0f};
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_handle);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(GLfloat), 4 * sizeof(GLfloat), glm::value_ptr(light_color));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);
    int w, h;
    std::tie(w, h) = frame_buffer_size();
    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);
    glUseProgram(program);
}

void SimpleShapeApplication::frame() {
    glBindVertexArray(vao_);
//    glDrawArrays(GL_TRIANGLES, 0, 3 * 6);
    glDrawElements(GL_TRIANGLES, 21 * 2, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}
