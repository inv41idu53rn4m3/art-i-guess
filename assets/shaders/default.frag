#version 330 core

in vec2 vertpos;
out vec4 colour;

uniform sampler2D tex;
uniform vec3 lpos;

void main () {
    //vec3 lpos = vec3(0.0, 0.0, -0.1);
    vec3 ldir = vec3(vertpos * 2 - 1.0, 0.0) - lpos;
    ldir = normalize(vec3(ldir.x, ldir.y, ldir.z));
    vec3 normal = texture(tex, vertpos).rgb * 2 - 1.0;
    float light = length(max(vec3(0.0), dot(ldir, normal)));
    for (int i = 1; i <= 10; i++) {
        if (light > 1.0 / i) {
            light = 1.0 / i;
            break;
        }
    }
    vec4 lcolour = vec4(1.0, 0.3, 0.5, 1.0);
    colour = vec4(max((lcolour * light).rgb, 0.0), 1.0);

    // Draw shadows
    //float h0 = length(c1);
    //for (int i = 0; i < 128; i++) {
    //    float d = float(i) / 1024;
    //    float h = length(texture(tex, vertpos + vec2(d, -d)));
    //    if (h - d * 9 > h0) {
    //        colour = vec4(0.0, 0.0, 0.1, 1.0);
    //        break;
    //    }
    //}
}

