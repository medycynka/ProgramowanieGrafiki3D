#version 410

out vec4 vertex_color;
layout(location=0) in vec4 a_vertex_position;
layout(location=1) in vec3 a_vertex_color;

layout(std140) uniform Matrices {
    mat4 pmv_;
};

void main() {
    gl_Position = pmv_ * a_vertex_position;
    vertex_color = vec4(a_vertex_color.xyz, 1.0f);
}
