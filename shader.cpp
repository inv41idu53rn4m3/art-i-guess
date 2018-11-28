#include "shader.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include <glad/glad.h>

using namespace std;

map<string, vector<string>> namedict;

void loadShaderNames() {
    ifstream file;
    file.open("assets/shaders/name_definitions");

    if (file.good()) {
        string line;
        // Each line in name definitions represents a shader program
        while (!getline(file, line).eof()) {
            // The first word is the name of the shader program
            int lastpos = line.find(" ");
            string name = line.substr(0, lastpos);

            // Splits each row by spaces, each entry is a filename
            // TODO: use a dedicated string parsing function
            vector<string> files;
            for (int i = 0; lastpos != string::npos; i++) {
                lastpos++; // This is to prevent writing lastpos + 1 multiple times
                int nextpos = line.find(" ", lastpos);
                files.push_back(line.substr(lastpos, nextpos - lastpos));
                lastpos = nextpos;
            }
            namedict[name] = files;
        }
    } else {
        clog << "Failed to load shader list" << endl;
    }
}

GLuint createShader(string source, GLenum type) {
    fstream file;
    // Open shader source file
    file.open(source.c_str(), file.in);
    char* src;

    if (file.good()) {
        // Get file size
        file.seekg(0, file.end);
        int length = file.tellg();
        file.seekg(0, file.beg);
        // Read file into string
        src = new char [length];
        file.read(src, length);
        file.close();

        // Make sure the shader is null terminated
        src[length] = 0;
    } else {
        clog << "Failed to open shader file: " << source << endl;
        // Make sure the missing shader is null terminated to prevent crashes
        src = new char;
        *src = 0;
    }

    // Create shader
    GLuint shader;
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    
    // Test if shader compiled correctly
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        cerr << "Shader compilation error:\n" << infoLog << endl;
    }

    return shader;
}

void linkShaderProgram(GLuint program) {
    glLinkProgram(program);
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cerr << "Shader program linking error:\n" << infoLog << endl;
    }
}

GLuint createLinkVFShaderProgram(string name) {
    if (!namedict[name].empty()) {
        string vertname = "assets/shaders/" + namedict[name][0];
        GLuint vertexShader = createShader(vertname, GL_VERTEX_SHADER);

        string fragname = "assets/shaders/" + namedict[name][1];
        GLuint fragmentShader = createShader(fragname, GL_FRAGMENT_SHADER);

        GLuint program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        linkShaderProgram(program);

        glDeleteShader(vertexShader); // Delete the now useless shader objects
        glDeleteShader(fragmentShader);

        return program;
    } else {
        clog << "Could not find shader: " << name << endl;
        return 0;
    }
}
