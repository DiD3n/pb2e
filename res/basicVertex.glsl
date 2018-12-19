#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textureCord;
layout(location = 2) in vec3 color;
uniform mat4 MVP;

out vec2 v_cord;
out vec3 v_color;

void main() {
   gl_Position = MVP * position;
   v_cord = textureCord;
   v_color = color;
}