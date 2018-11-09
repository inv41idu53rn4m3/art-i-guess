#version 330 core

in vec2 vertpos;
out vec4 colour;

uniform sampler2D tex;

void main () {
    vec3 lpos = vec3(0.0, 0.0, -0.5);
    vec3 ldir = vec3(vertpos * 2 - 1.0, 0.0) - lpos;
    ldir = normalize(vec3(ldir.x, ldir.y, ldir.z));
    vec3 normal = texture(tex, vertpos).rgb * 2 - 1.0;
    float light = length(max(vec3(0.0), dot(ldir, normal)));
    vec4 lcolour = vec4(0.5, 0.5, 0.4, 1.0);
    colour = vec4((lcolour * light).rgb, 1.0);

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

