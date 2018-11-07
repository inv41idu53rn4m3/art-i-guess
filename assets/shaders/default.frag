#version 330 core

in vec2 vertpos;
out vec4 colour;

uniform sampler2D tex;

void main () {
    vec4 c1 = texture(tex, vertpos);
    vec4 c2 = texture(tex, vec2(vertpos.x + 1.0 / 1024, vertpos.y - 1.0 / 1024));
    vec4 light = max(vec4(0.0), c1 - c2);
    vec4 shadow = max(vec4(0.0), c2 - c1);
    vec4 lcolour = vec4(1.0, 0.5, 0.1, 1.0);
    vec4 bcolour = vec4(0.0);
    colour = vec4(vec3(0.3) + (bcolour * c1 + lcolour * light * 20 - lcolour * shadow * 20).rgb, 1.0);

    // Draw shadows
    float h0 = length(c1);
    for (int i = 0; i < 128; i++) {
        float d = float(i) / 1024;
        float h = length(texture(tex, vertpos + vec2(d, -d)));
        if (h - d * 9 > h0) {
            colour = vec4(0.0, 0.0, 0.1, 1.0);
        }
    }
}

