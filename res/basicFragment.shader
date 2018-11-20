#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_pos;

void main() {
    color = vec4(v_pos.x,v_pos.y,v_pos.z,1.0);
}