#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include <glad/glad.h>

using namespace std;

void loadTexture(const string& filename);
void setTexUniform(const string& name, GLuint texture, GLuint program);
GLuint genTexture(bool interpolate, bool tile, float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);

#endif
