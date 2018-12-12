#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textureCord;

out vec2 v_cord;

void main() {
   gl_Position = position;
   v_cord = textureCord;
}