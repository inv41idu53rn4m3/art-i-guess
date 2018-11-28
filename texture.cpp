#include "texture.hpp"

#include <iostream>
#include <vector>

#include <lodepng/lodepng.h>
#include <glad/glad.h>

using namespace std;

void loadTexture(const string& filename) {
    // Load texture from file
    vector<unsigned char> buffer;
    unsigned int w, h;
    unsigned int error = lodepng::decode(buffer, w, h, filename.c_str());
    if (error) {
        clog << "Failed to load texture: " << filename << endl;
        clog << "LodePNG error " << error << ": " << lodepng_error_text(error) << endl;
    }

    // Upload texture to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer.data());
}

GLuint genTexture(bool interpolate, GLint wrap, float r, float g, float b, float a) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    if (interpolate) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    if (wrap == GL_CLAMP_TO_BORDER) {
        float borderColor[] = {r, g, b, a};
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    }

    return texture;
}

void setTexUniform(const string& name, GLuint texture, GLuint program) {
    GLint texpos = glGetUniformLocation(program, name.c_str());
    glUniform1i(texpos, texture);
}

