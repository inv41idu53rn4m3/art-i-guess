#include <iostream>
#include <vector>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.hpp"
#include "shader.hpp"
#include "texture.hpp"

using namespace std;
int main(int argc, char const *argv[]) {
    GLFWwindow* window = setupWindow(600, 600, "noname", false);

    // Vertex input
    vector<GLfloat> vertices = {
        -1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f,
         1.0f, -1.0f
    };

    vector<GLuint> elements = {
        0, 1, 2, 0, 2, 3
    };

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Upload vertex data
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLuint), elements.data(), GL_STATIC_DRAW);

    // Set up shaders
    GLuint program = createLinkVFShaderProgram("assets/shaders/default");
    glUseProgram(program);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
    GLuint texture = loadTexture("assets/textures/normal.png");
    GLint texpos = glGetUniformLocation(program, "tex");
    glUniform1ui(texpos, texture);

    glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    unsigned int framecount = 0;
    glfwSetTime(0);
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        float lx = sin(glfwGetTime());
        float ly = cos(glfwGetTime());
        glUniform3f(glGetUniformLocation(program, "lpos"), lx, ly, -0.1);

        // Draw stuff
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        framecount++;
    }

    cout << framecount / glfwGetTime() << "fps" << endl;

    glfwTerminate();
    return 0;
}
