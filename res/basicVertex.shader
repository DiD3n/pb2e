#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 pos;

out vec3 v_pos;

void main() {
   gl_Position = position;
   v_pos = pos;
}