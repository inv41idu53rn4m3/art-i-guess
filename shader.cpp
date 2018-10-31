#include "shader.hpp"

using namespace std;
GLuint createShader(string source, GLenum type) {
    fstream file;
    // Open shader source file
    file.open(source.c_str(), file.in);
    int length;
    char* src;
    if (file.good()) {
        // Get file size
        file.seekg(0, file.end);
        length = file.tellg();
        file.seekg(0, file.beg);
        // Read file into string
        src = new char [length];
        file.read(src, length);
        file.close();
    } else {
        clog << "Failed to open shader file: " << source << endl;
        length = 0;
        src = new char[0];
    }
    // Make sure the shader is null terminated
    src[length] = 0;
    // Create shader
    GLuint shader;
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    // Test if shader compiled correctly
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        cerr << "Shader compilation error:\n" << infoLog << endl;
    }
    return shader;
}

void linkShaderProgram(GLuint program) {
    glLinkProgram(program);
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cerr << "Shader program linking error:\n" << infoLog << endl;
    }
}

GLuint createLinkVFShaderProgram(string name) {
    clog << "Creating vertex shader" << endl;
    string vertname = name;
    vertname += ".vert";
    GLuint vertexShader = createShader(vertname, GL_VERTEX_SHADER);
    clog << "Creating fragment shader" << endl;
    string fragname = name;
    fragname += ".frag";
    GLuint fragmentShader = createShader(fragname, GL_FRAGMENT_SHADER);
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    linkShaderProgram(program);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}
