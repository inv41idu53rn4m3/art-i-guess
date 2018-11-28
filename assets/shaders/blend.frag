#version 330 core

in vec2 vertpos;
out vec4 colour;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main () {
    colour = texture(tex1, vertpos) + texture(tex2, vertpos);
    //colour = vec4((texture(tex1, vertpos) - texture(tex2, vertpos)).rgb, 1.0);
    //colour = texture(tex2, vertpos);
}

