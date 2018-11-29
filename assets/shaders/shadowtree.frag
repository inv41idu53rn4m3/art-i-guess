#version 330 core

in vec2 vertpos;
out vec4 colour;

uniform sampler2D tex;

void main () {
    int w = 1536;
    int h = 1024;
    if (vertpos.x * w < 1024) {
        colour = texture(tex, vec2(vertpos.x / 1024 * w, vertpos.y));
    } else {
        ivec2 pos;
        int depth = 2;
        int miny = 0;
        int inty = int(vertpos.y * h);
        while (inty > miny + h / depth) {
            miny += h / depth;
            depth <<= 1;
        }

        pos.x = int(vertpos.x * w) - 1024;
        pos.y = inty - miny;

        vec4 maxbright = vec4(0.0);
        for (int x = pos.x * depth; x < (pos.x + 1) * depth; x++) {
            for (int y = pos.y * depth; y < (pos.y + 1) * depth; y++) {
                maxbright = max(maxbright, texture(tex, vec2(float(x) / 1024, float(y) / 1024)));
            }
        }
        colour = maxbright;
    }
}

