#include "window.hpp"

using namespace std;

void resize_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

GLFWwindow* setupWindow(int w, int h, string title, bool resizable) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, resizable);

    glfwWindowHint(GLFW_SAMPLES, 16);

    GLFWwindow* window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
    if (window == NULL) {
        clog << "Failed to create GLFW window" << endl;
    }

    if (resizable) {
        glfwSetFramebufferSizeCallback(window, resize_callback);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, w, h);

    glEnable(GL_MULTISAMPLE);

    return window;
}
