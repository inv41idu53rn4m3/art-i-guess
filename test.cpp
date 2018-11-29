#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "framebuffer.hpp"

using namespace std;

int w = 600, h = 600; // Window height and width
void resizeCallback(GLFWwindow* window, int width, int height) {
    w = width;
    h = height;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main(int argc, char const *argv[]) {
    GLFWwindow* window = setupWindow(w, h, "noname", true, true);
    glfwSetWindowSizeCallback(window, resizeCallback);
    glfwSetKeyCallback(window, keyCallback);

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

    GLuint VBO; // Generate vertex buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Upload vertex data
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    GLuint EBO; // Generate element buffer
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Upload element data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLuint), elements.data(), GL_STATIC_DRAW);

    // Set up shaders
    loadShaderNames();
    GLuint default_program = createLinkVFShaderProgram("default");
    GLuint blurh = createLinkVFShaderProgram("blurh"); // Horizontal blur
    GLuint blurv = createLinkVFShaderProgram("blurv"); // Vertical blur
    GLuint blend = createLinkVFShaderProgram("blend");
    GLuint gentree = createLinkVFShaderProgram("gentree");

    // Define vertex data format
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*) 0);
    glEnableVertexAttribArray(0);

    glUseProgram(default_program);
    glActiveTexture(GL_TEXTURE0);
    genTexture();
    loadTexture("assets/textures/normal2.png");
    setTexUniform("normal", 0, default_program);

    glActiveTexture(GL_TEXTURE6);
    genTexture();
    loadTexture("assets/textures/diffuse.png");
    setTexUniform("diffuse", 6, default_program);

    glActiveTexture(GL_TEXTURE7);
    genTexture();
    loadTexture("assets/textures/spectral.png");
    setTexUniform("spectral", 7, default_program);

    glActiveTexture(GL_TEXTURE1);
    genTexture();
    loadTexture("assets/textures/bump2.png");

    // Generate framebuffers
    glActiveTexture(GL_TEXTURE2);
    auto main_fb = genFB(1024, 1024);
    glActiveTexture(GL_TEXTURE3);
    auto blurh_fb = genFB(1024, 1024);
    glActiveTexture(GL_TEXTURE4);
    auto blurv_fb = genFB(1024, 1024);
    glActiveTexture(GL_TEXTURE5);
    auto shadowtree = genFB(1536, 1024);

    // Set basic OpenGL settings
    glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Generate shadowtree in framebuffer
    glViewport(0, 0, 1536, 1024);
    glUseProgram(gentree);
    setTexUniform("tex", 1, gentree);
    glBindFramebuffer(GL_FRAMEBUFFER, get<1>(shadowtree));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glUseProgram(default_program);
    setTexUniform("height", 5, default_program);

    unsigned int framecount = 0;
    glfwSetTime(0);
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Draw stuff
        glViewport(0, 0, 1024, 1024);
        glUseProgram(default_program);
        // Calculate position of moving light
        float t = glfwGetTime();
        float lx = sin(t / 7.0) * 0.1 + 0.7;
        float ly = cos(t) * 0.03 - 0.8;
        float lz = cos(t / 10.0) * 0.3 - 0.6;
        float lb = sin(t / 10.0) * 0.1 + 0.9;
        glUniform3f(glGetUniformLocation(default_program, "lpos"), lx, ly, lz);
        glUniform1f(glGetUniformLocation(default_program, "lbright"), lb);
        glBindFramebuffer(GL_FRAMEBUFFER, get<1>(main_fb));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Blur
        glUseProgram(blurh);
        glUniform1f(glGetUniformLocation(blurh, "w"), 1024.0);
        setTexUniform("framebuffer", 2, blurh);
        glBindFramebuffer(GL_FRAMEBUFFER, get<1>(blurh_fb));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        /*
        for (int i = 0; i < 10; i++) {
            glUseProgram(blurv);
            glUniform1f(glGetUniformLocation(blurv, "h"), 1024.0);
            setTexUniform("framebuffer", 3, blurv);
            glBindFramebuffer(GL_FRAMEBUFFER, get<1>(blurv_fb));
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glUseProgram(blurh);
            glUniform1f(glGetUniformLocation(blurh, "w"), 1024.0);
            setTexUniform("framebuffer", 4, blurh);
            glBindFramebuffer(GL_FRAMEBUFFER, get<1>(blurh_fb));
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        */
        glUseProgram(blurv);
        glUniform1f(glGetUniformLocation(blurv, "h"), 1024.0);
        setTexUniform("framebuffer", 3, blurv);
        glBindFramebuffer(GL_FRAMEBUFFER, get<1>(blurv_fb));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // End of blur

        // Finally blend unblurred and blurred textures
        glViewport((w - min(w, h)) / 2, (h - min(w, h)) / 2, min(w, h), min(w, h));
        glUseProgram(blend);
        setTexUniform("tex1", 2, blend);
        setTexUniform("tex2", 4, blend);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        framecount++;
    }

    cout << framecount / glfwGetTime() << "fps" << endl;

    glfwTerminate();
    return 0;
}
