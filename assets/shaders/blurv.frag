#version 330 core

in vec2 vertpos;
out vec4 colour;

uniform float h;
uniform sampler2D framebuffer;

void main () {
    float offsety = 1.0 / h;

    colour = texture(framebuffer, vertpos + vec2(0.0, -offsety * 2)) * 0.2;
    colour += texture(framebuffer, vertpos + vec2(0.0, -offsety)) * 0.2;
    colour += texture(framebuffer, vertpos + vec2(0.0, 0.0)) * 0.2;
    colour += texture(framebuffer, vertpos + vec2(0.0, offsety)) * 0.2;
    colour += texture(framebuffer, vertpos + vec2(0.0, offsety * 2)) * 0.2;
}

