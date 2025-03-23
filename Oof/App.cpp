#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "App.h"

App::App(int width, int height, const char* title) {
    this->width = width;
    this->height = height;
    this->title = title;
    this->window = NULL;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);        
}

int App::run() {
    this->window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (this->window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(this->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);

    return 0;
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 
