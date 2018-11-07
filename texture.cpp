#include "texture.hpp"

using namespace std;

GLuint loadTexture(string filename) {
    // Load texture from file
    vector<unsigned char> buffer;
    unsigned int w, h;
    unsigned int error = lodepng::decode(buffer, w, h, filename.c_str());
    if (error) {
        clog << "Failed to load texture: " << filename << endl;
        clog << "LodePNG error " << error << ": " << lodepng_error_text(error) << endl;
    }


    // Upload texture to GPU
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer.data());

    return texture;
}
