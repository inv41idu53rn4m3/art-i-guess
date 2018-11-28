#version 330 core

in vec2 vertpos;
out vec4 colour;

uniform float w;
uniform sampler2D framebuffer;

void main () {
    float offsetx = 1.0 / w;

    colour = texture(framebuffer, vertpos + vec2(-offsetx * 2, 0.0)) * 0.2;
    colour += texture(framebuffer, vertpos + vec2(-offsetx, 0.0)) * 0.2;
    colour += texture(framebuffer, vertpos + vec2(0.0, 0.0)) * 0.2;
    colour += texture(framebuffer, vertpos + vec2(offsetx, 0.0)) * 0.2;
    colour += texture(framebuffer, vertpos + vec2(offsetx * 2, 0.0)) * 0.2;
}

