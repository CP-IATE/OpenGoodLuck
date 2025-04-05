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
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};
float colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};
float indices[] = {
    0, 1, 2
};

int Engine::run() {
	App app(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_DISPLAY_NAME);
    if (app.run() == -1) {
        return -1;
    };

    Shader shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
    Figure figure(vertices, 9, indices, 3, colors, 9);
    figure.setShader(&shader);
    figure.setupVertexObjects();

    while (!glfwWindowShouldClose(app.window))
    {
        // input
        processInput(app.window);

        // rendering commands here
        figure.draw();

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
