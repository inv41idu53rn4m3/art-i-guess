#include <iostream>
#include <tuple>

#include <glad/glad.h>

#include "texture.hpp"
#include "framebuffer.hpp"

using namespace std;

tuple<GLuint, GLuint> genFB(GLuint w, GLuint h, bool alpha, GLint wrap) {
    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    GLuint texture = genTexture(true, wrap);
    if (alpha) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); 
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); 
    }
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        clog << "Failed to create framebuffer" << endl;
    }
    
    return make_tuple(texture, fbo);
}
