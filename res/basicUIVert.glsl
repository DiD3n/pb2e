#version 330 core

layout(location = 0) in vec4 position;
layout(location = 2) in vec4 color;
uniform mat4 MVP;

out vec4 v_color;

void main() {
   gl_Position = MVP * position;
   v_color = color;
}