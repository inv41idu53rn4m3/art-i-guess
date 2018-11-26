#version 330 core

in vec2 vertpos;
out vec4 colour;

uniform sampler2D normal;
uniform sampler2D height;
uniform vec3 lpos;

void main () {
    vec3 ldir = vec3(vertpos * 2 - 1.0, texture(height, vertpos).r) - lpos;
    float ldist = length(ldir);
    ldir = normalize(ldir);
    vec3 normalv = texture(normal, vertpos).rgb * 2 - 1.0;
    float light = max(0.0, dot(ldir, normalv)) / ldist;
    //for (int i = 1; i <= 10; i++) {
    //    if (light > 1.0 / i) {
    //        light = 1.0 / i;
    //        break;
    //    }
    //}
    vec4 lcolour = vec4(0.9, 0.2, 0.5, 1.0);
    colour = vec4(clamp((lcolour * light).rgb, +0.0, 1.0), 1.0);

    // Draw shadows
    float h0 = length(texture(height, vertpos));
    for (int i = 0; i < 128; i++) {
        float d = float(i) / 1024.0;
        float h = length(texture(height, vertpos + ldir.xy * -d * ldist));
        if (h - d * 2 > h0) {
            colour = vec4(0.0, 0.0, 0.0, 1.0);
            return;
        }
    }
}

