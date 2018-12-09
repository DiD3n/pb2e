#version 330 core

uniform vec4 mod;

layout(location = 0) out vec4 color;

in vec4 v_color;

void main() {
    color = vec4(v_color.x+mod,v_color.y+mod,v_color.z+mod,mod);
}