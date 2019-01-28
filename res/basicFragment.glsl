#version 330 core

uniform sampler2D tex;

layout(location = 0) out vec4 color;

in vec2 v_cord;
in vec3 v_color;

void main() {

    if (v_color != vec3(0.f))
        color = texture(tex,v_cord) * vec4(v_color,1.0f);
    else
        color = texture(tex,v_cord);
}