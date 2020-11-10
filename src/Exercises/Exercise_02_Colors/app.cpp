//
// Created by pbialas on 25.09.2020.
//

#include "app.h"

#include <iostream>
#include <vector>
#include <tuple>


#include "Application/utils.h"

void SimpleShapeApplication::init() {


    auto program = xe::create_program(std::string(PROJECT_DIR) + "/shaders/base_vs.glsl",
                                      std::string(PROJECT_DIR) + "/shaders/base_fs.glsl");


    if (!program) {
        std::cerr << "Cannot create program from " << std::string(PROJECT_DIR) + "/shaders/base_vs.glsl" << " and ";
        std::cerr << std::string(PROJECT_DIR) + "/shaders/base_fs.glsl" << " shader files" << std::endl;
    }

    std::vector<GLfloat> vertices = {
            -0.8f, 0.5f, 0.0f, /* first vertex */ 0.4f, 0.0f, 0.0f, /* color */
            -0.1f, 0.5f, 0.0f, /* second vertex */ 0.9f, 0.7f, 0.0f,
            -0.45f, 0.8f, 0.0f, /* third vertex */ 0.4f, 0.0f, 0.9f,
            -0.8f, -0.5f, 0.0f, 0.63f, 0.45f, 0.41f,
            -0.1f, 0.5f, 0.0f, 0.63f, 0.45f, 0.41f,
            -0.8f, 0.5f, 0.0f, 0.63f, 0.45f, 0.41f,
            -0.8f, -0.5f, 0.0f, 0.63f, 0.45f, 0.41f,
            -0.1f, -0.5f, 0.0f, 0.63f, 0.45f, 0.41f,
            -0.1f, 0.5f, 0.0f, 0.63f, 0.45f, 0.41f,
            0.1f, 0.5f, 0.0f, /* second house */ 0.05f, 0.47f, 0.06f,
            0.8f, 0.5f, 0.0f, 0.05f, 0.47f, 0.06f,
            0.45f, 0.8f, 0.0f, 0.05f, 0.47f, 0.06f,
            0.1f, -0.5f, 0.0f, 0.54f, 0.8f, 0.89f,
            0.8f, 0.5f, 0.0f, 0.54f, 0.8f, 0.89f,
            0.1, 0.5f, 0.0f, 0.54f, 0.8f, 0.89f,
            0.1f, -0.5f, 0.0f, 0.54f, 0.8f, 0.89f,
            0.8f, -0.5f, 0.0f, 0.54f, 0.8f, 0.89f,
            0.8f, 0.5f, 0.0f, 0.54f, 0.8f, 0.89f
    };

    GLuint v_buffer_handle;
    glGenBuffers(1, &v_buffer_handle);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);
    int w, h;
    std::tie(w, h) = frame_buffer_size();
    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);
    glUseProgram(program);
}

void SimpleShapeApplication::frame() {
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 3 * 6);
    glBindVertexArray(0);
}