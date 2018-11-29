#include "window.hpp"

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

GLFWwindow* setupWindow(int w, int h, string title, bool resizable, bool fullscreen) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, resizable);

    glfwWindowHint(GLFW_SAMPLES, 16);

    GLFWwindow* window;
    if (fullscreen) {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        window = glfwCreateWindow(mode->width, mode->height, title.c_str(), glfwGetPrimaryMonitor(), NULL);
    } else {
        window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
    }
    
    if (window == NULL) {
        clog << "Failed to create GLFW window" << endl;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, w, h);

    glEnable(GL_MULTISAMPLE);

    return window;
}
