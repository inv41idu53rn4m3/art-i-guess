#version 330 core

in vec2 vertpos;
out vec4 colour;

uniform sampler2D tex;

void main () {
    vec2 tpos = vec2(vertpos.x, vertpos.y + vertpos.x);
    colour = texture(tex, tpos);
}
