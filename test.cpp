#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.hpp"
#include "shader.hpp"

using namespace std;
int main(int argc, char const *argv[]) {
    GLFWwindow* window = setupWindow(600, 600, "noname", false);

    // Vertex input
    GLfloat vertices[] = {
        -1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f,
         1.0f, -1.0f
    };

    GLuint elements[] = {
        0, 1, 2, 0, 2, 3
    };

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Upload vertex data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    // Set up shaders
    GLuint program = createLinkVFShaderProgram("assets/shaders/default");
    glUseProgram(program);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw stuff
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
