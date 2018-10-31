#include <string>
#include <iostream>
#include <fstream>

#include <glad/glad.h>

GLuint createShader(std::string source, GLenum type);
void linkShaderProgram(GLuint program);
GLuint createLinkVFShaderProgram(std::string name);
