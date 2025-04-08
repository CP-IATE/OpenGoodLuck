#include "Engine.h"
#include "App.h"
#include "Shader.h"
#include "Figure.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
float vertices[] = {
    -0.25f, -0.5f, 0.25f,
    -0.25f, -0.5f, -0.25f,
    0.25f, -0.5f, -0.25f,
    0.25f, -0.5f, 0.25f,
    -0.25f, 0.0f, 0.25f,
    -0.25f, 0.0f, -0.25f,
    0.25f, 0.0f, -0.25f,
    0.25f, 0.0f, 0.25f,
    0.0f, 0.4f, 0.0f
};
float colors[] = {
    0.0745098f, 0.0745098f, 0.333333f,
    0.0745098f, 0.0745098f, 0.333333f,
    0.0745098f, 0.0745098f, 0.333333f,
    0.0745098f, 0.0745098f, 0.333333f,
    0.0745098f, 0.0745098f, 0.333333f,
    0.0745098f, 0.0745098f, 0.333333f,
    0.0745098f, 0.0745098f, 0.333333f,
    0.0745098f, 0.0745098f, 0.333333f,
    0.0745098f, 0.0745098f, 0.333333f
};
GLuint indices[] = {
    0, 1, 1, 2, 2, 3, 3, 0,
    0, 4, 4, 7, 7, 3, 7, 6,
    6, 2, 6, 5, 5, 1, 5, 4,
    8, 4, 8, 5, 8, 6, 8, 7
};

int Engine::run() {
	App app(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_DISPLAY_NAME);
    if (app.run() == -1) {
        return -1;
    };

    Shader shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
    Figure figure(vertices, 27, indices, 32, colors, 27);
    figure.setShader(&shader);
    figure.setupVertexObjects();

    while (!glfwWindowShouldClose(app.window))
    {
        // input
        processInput(app.window);

        // rendering commands here
        figure.draw(WINDOW_WIDTH, WINDOW_HEIGHT);

        // check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(app.window);
    }

    glfwTerminate();
    return 0;
}

void Engine::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
