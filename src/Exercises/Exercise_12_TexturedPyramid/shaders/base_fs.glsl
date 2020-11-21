#version 410

in vec2 vertex_color;
layout(location=0) out vec4 vFragColor;

uniform sampler2D diffuse_map;

void main() {
    vFragColor = texture(diffuse_map, vertex_color);
}
