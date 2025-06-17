#include "Engine.h"
#include "App.h"
#include "Shader.h"
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <iostream>
#include "miniaudio.h"
#include "Music.h"
#include "Model.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int Engine::run() {
	App app(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_DISPLAY_NAME);
    if (app.run() == -1) {
        return -1;
    };

    Shader shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
    Model model(PEAK_MODEL);
    Music music(AUDIO_FILE);
    music.start();
    
    bool running = true;

    while (running) {
        PollEvents(running);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        rotateView(shader);
        model.Draw(shader);
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

void rotateView(Shader& shader) {
    glm::mat4 modelMat = glm::mat4(1.0f);
    float time = SDL_GetTicks() / 1000.0f;
    modelMat = glm::rotate(modelMat, time * 3.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 view = glm::lookAt(
        glm::vec3(3.0f, 4.0f, 6.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);

    shader.use();
    shader.setMat4("model", modelMat);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
}
