#version 410

in vec4 vertex_color;
layout(location=0) out vec4 vFragColor;
layout(location=1) out mat4 pvm_;

layout(std140) uniform Modifiers {
    float light_intensity;
    vec3 light_color;
    mat4 pvm_;
};

void main() {
    vFragColor.a = vertex_color.a;
    vFragColor.rgb = light_intensity * light_color * vertex_color.rgb;
}
