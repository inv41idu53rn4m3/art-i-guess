#version 330 core

in vec2 vertpos;
out vec4 colour;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main () {
    vec3 c1 = texture(tex1, vertpos).rgb;
    vec3 c2 = texture(tex2, vertpos).rgb;
    colour = vec4(c1 + c2, 1.0);
    //colour = vec4((texture(tex1, vertpos) - texture(tex2, vertpos)).rgb, 1.0);
    //colour = texture(tex2, vertpos);
}

