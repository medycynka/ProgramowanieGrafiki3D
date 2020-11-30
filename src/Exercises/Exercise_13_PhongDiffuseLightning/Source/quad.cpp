#include "../Headers/quad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "3rdParty/src/stb/stb_image.h"

Quad::Quad(int program_id) {
    // Sending indices and vertices buffers to shaders
    glGenBuffers(1, &buffer_[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenBuffers(1, &buffer_[1]);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_[1]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_[0]);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_[1]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(5 * sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Loading texture for quad
    int width, height, n_channels;
    auto texture_filename = std::string(PROJECT_DIR) + "/Textures/silver_2.png";
    data_ = stbi_load(texture_filename.c_str(), &width, &height, &n_channels, 0);

    if(data_){
        std::cout << "Successfully loaded texture " << texture_filename << "\n";
        std::cout << "Read values: " << "\n";
        std::cout << "Width: " << width << "\n";
        std::cout << "Height: " << height << "\n";
        std::cout << "Number of channels: " << n_channels << "\n";
    } else{
        std::cerr << "Error, couldn't load " << texture_filename << "." << "\n";
    }

    glBindTexture(GL_TEXTURE_2D, diffuse_texture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    auto u_light_index = glGetUniformBlockIndex(program_id, "Light");
    if (u_light_index == GL_INVALID_INDEX) {
        std::cout << "Cannot find Light uniform block in program" << "\n";
    } else {
        glUniformBlockBinding(program_id, u_light_index, 2);
    }

    // Light
    old_position_ = glm::vec4(0.0f, 0.0f, 2.0f, 1.0f);
    light_.position = old_position_;
    light_.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    light_.a = glm::vec4(1.0f, 0.0f, 1.0f, 0.0f);
}

Quad::~Quad(){
    stbi_image_free(data_);
}

void Quad::update_light_position(const glm::mat4 &mv_) {
    light_.position = old_position_ * mv_;
}

void Quad::draw() {
    // sending updated light to shader
    glGenBuffers(1, &u_light_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, u_light_buffer);
    glBufferData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::vec4), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), &light_.position);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec4), &light_.color);
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4), sizeof(glm::vec4), &light_.a);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 2, u_light_buffer);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuse_texture_);
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}