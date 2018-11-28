#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <tuple>

#include <glad/glad.h>

using namespace std;

tuple<GLuint, GLuint> genFB(GLuint w, GLuint h, bool alpha = false, GLint wrap = GL_CLAMP_TO_EDGE);

#endif
