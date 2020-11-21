#include "../Headers/pyramid.h"

#define STB_IMAGE_IMPLEMENTATION
#include "3rdParty/src/stb/stb_image.h"

Pyramid::Pyramid() {
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Loading texture for pyramid
    int width, height, n_channels;
    auto texture_filename = std::string(PROJECT_DIR) + "/Textures/multicolor.png";
    data_ = stbi_load(texture_filename.c_str(), &width, &height, &n_channels, 0);

    if(data_){
        std::cout << "Successfully loaded texture multicolor.png" << "\n";
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
}

Pyramid::~Pyramid(){
    stbi_image_free(data_);
}

void Pyramid::draw() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuse_texture_);
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
