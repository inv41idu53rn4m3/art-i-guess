#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* setupWindow(int w, int h, std::string title, bool resizable);

#endif
