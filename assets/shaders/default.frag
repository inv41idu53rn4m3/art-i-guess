#version 330 core

in vec2 vertpos;
out vec4 colour;

uniform sampler2D normal;
uniform sampler2D height;
uniform sampler2D diffuse;
uniform sampler2D spectral;
uniform vec3 lpos;
uniform float lbright;

vec4 get_tree_sample(vec2 pos, int depth) {
    if (pos.y < 0.0 || pos.y > 1.0 || pos.x < 0.0 || pos.x > 1.0) {
        return vec4(0.0);
    }

    if (depth == 1) {
        return texture(height, pos * vec2(1024.0 / 1536.0, 1.0));
    } else {
        int ypos = 0;
        for (int a = 512, i = 2; i < depth; a /= 2, i++) {
            ypos += a;
        }
        pos /= float(1 << (depth - 1));

        return texture(height, vec2((pos.x + 1.0) * 1024.0 / 1536.0, pos.y + float(ypos) / 1024.0));
    }
}

void main () {
    // Diffuse
    vec3 ldir = vec3(vertpos * 2 - 1.0, get_tree_sample(vertpos, 1).r) - lpos;
    float ldist = length(ldir);
    vec3 ldirn = normalize(ldir);
    vec3 normalv = texture(normal, vertpos).rgb * 2 - 1.0;
    float light = max(0.0, dot(ldirn, normalv)) / ldist * texture(diffuse, vertpos).r;

    // Specular
    light += pow(max(0.0, dot(reflect(-ldirn, normalv), normalize(vec3(vertpos * 2 - 1.0, 1.0)))), 2.0) * texture(spectral, vertpos).r;

    // Draw shadows
    float h0 = get_tree_sample(vertpos, 1).r;
    float incr = 1.0 / 1024.0;
    float dist = incr;
    float ldisth = length(ldir.xy);
    int depth = 1;
    while (ldisth > dist + incr && depth < 5) {
        float h = get_tree_sample(vertpos + dist * -ldirn.xy, depth).r;
        h -= h0;
        if (h / dist * ldisth > ldir.z) {
            light *= 1.0 - h / dist;
            break;
        }
        if (dist > incr * 4) {
            incr *= 2.0;
            depth++;
        }
        dist += incr;
    }

    // Quantize
    //for (int i = 1; i <= 15; i++) {
    //    if (light > 1.0 / i) {
    //        light = 1.0 / i;
    //        break;
    //    }
    //}

    // Final colour
    vec4 lcolour = vec4(1.2, 0.9, 0.5, 1.0);
    vec4 scolour = vec4(0.01, 0.02, 0.03, 1.0);
    light *= lbright;
    colour = vec4((lcolour * light + scolour * (1.0 - light)).rgb, 1.0) + scolour;
    return;
}

