#version 330 core
layout (location = 0) in vec2 pos;
out vec2 vertpos;

void main () {
    vertpos = vec2(pos.x / 2.0 + 0.5, pos.y / 2.0 + 0.5);
    gl_Position = vec4(pos, 0.0f, 1.0f);
}
