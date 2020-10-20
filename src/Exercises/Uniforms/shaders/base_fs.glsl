#version 410

in vec3 vertex_color;
layout(location=0) out vec4 vFragColor;

layout(std140) uniform Modifiers {
    float light_intensity;
    vec3 light_color;
};

void main() {
    vFragColor.a = light_intensity;
    vFragColor.rgb = light_color * vertex_color;
}
