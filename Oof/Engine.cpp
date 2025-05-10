#include "Engine.h"
#include "App.h"
#include "Shader.h"
#include "Figure.h"
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <iostream>
#include "miniaudio.h"
#include "Music.h"

#define AUDIO_FILE "funkytown.mp3"

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

    Music music(AUDIO_FILE);
    music.start();
    
    bool running = true;

    while (running) {
        PollEvents(running);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        figure.update(WINDOW_WIDTH, WINDOW_HEIGHT);
        figure.draw();
        SDL_GL_SwapWindow(app.window);
    }

    music.end();
    SDL_Quit();
    return 0;
}

void Engine::PollEvents(bool& running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
            running = false;
            break;

        case SDL_EVENT_WINDOW_RESIZED:
            framebuffer_size_callback(event.window.data1, event.window.data2);
            break;

        case SDL_EVENT_KEY_DOWN:
            if (event.key.key == SDLK_ESCAPE)
                running = false;
            break;
        }
    }
}
