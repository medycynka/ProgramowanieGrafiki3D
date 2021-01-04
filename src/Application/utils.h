//
// Created by pbialas on 05.08.2020.
//


#pragma once

#include <string>

#include "glad/glad.h"
#include "3rdParty/src/stb/stb_image.h"

namespace xe {
    namespace utils {

        std::string load_file(const std::string &path);

        std::string get_gl_description();

        std::string shader_type(GLenum type);

        void set_uniform1i(GLuint program, const std::string& name, int value);

        void set_uniform_block_binding(GLuint program, const std::string &name, GLuint binding);

        void load_texture(const std::string &filename);
    }

    GLuint create_shader_from_file(GLenum type, const std::string &path);

    GLuint link_program(GLuint program);

    GLuint create_program(const std::string &vs_path, const std::string &fs_path);



}