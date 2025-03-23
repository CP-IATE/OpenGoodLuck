#include "Engine.h"
#include "App.h"
#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int Engine::run() {
	App app(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_DISPLAY_NAME);
    if (app.run() == -1) {
        return -1;
    };
    Shader shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

    while (!glfwWindowShouldClose(app.window))
    {
        // input
        processInput(app.window);

        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader.shaderProgram);
        glBindVertexArray(shader.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(app.window);
    }

    glDeleteVertexArrays(1, &shader.VAO);
    glDeleteBuffers(1, &shader.VBO);
    glDeleteProgram(shader.shaderProgram);

    glfwTerminate();
    return 0;
}

void Engine::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
