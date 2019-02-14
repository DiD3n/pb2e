#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 color;
uniform mat4 MVP;

out vec4 v_color;

void main() {
   gl_Position = MVP * vec4(position,0.f,1.f);
   v_color = color;
}