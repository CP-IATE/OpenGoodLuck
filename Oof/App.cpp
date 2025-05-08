#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <iostream>
#include "App.h"

App::App(int width, int height, const char* title) {
    this->width = width;
    this->height = height;
    this->title = title;
    this->window = NULL;   

    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

int App::run() {
    this->window = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (this->window == NULL)
    {
        std::cout << "Failed to create SDL window" << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(this->window);
    if (!context) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(this->window);
        SDL_Quit();
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, width, height);

    return 0;
}

void framebuffer_size_callback(int width, int height)
{
    glViewport(0, 0, width, height);
} 
