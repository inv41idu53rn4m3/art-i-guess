#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <glad/glad.h>
 
void loadShaderNames();
GLuint createShader(std::string source, GLenum type);
void linkShaderProgram(GLuint program);
GLuint createLinkVFShaderProgram(std::string name);

#endif
