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

    glEnable(GL_DEPTH_TEST);

    Shader shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
    Model model(PEAK_MODEL);
    Music music(AUDIO_FILE);
    music.start();
    
    bool running = true;
    setupLight(shader);

    while (running) {
        PollEvents(running);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

void setupLight(Shader& lightingShader) {
    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };


    lightingShader.setVec3("viewPos", glm::vec3(3.0f, 4.0f, 6.0f));
    lightingShader.setFloat("material.shininess", 32.0f);

    /*
       Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
       the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
       by defining light types as classes and set their values in there, or by using a more efficient uniform approach
       by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
    */
    // directional light
    lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    lightingShader.setVec3("dirLight.ambient", 0.2f, 0.2f, 0.2f);
    lightingShader.setVec3("dirLight.diffuse", 0.0f, 0.0f, 0.0f);
    lightingShader.setVec3("dirLight.specular", 0.0f, 0.0f, 0.0f);
    // point light 1
    lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
    lightingShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    lightingShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    lightingShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    lightingShader.setFloat("pointLights[0].constant", 1.0f);
    lightingShader.setFloat("pointLights[0].linear", 0.09f);
    lightingShader.setFloat("pointLights[0].quadratic", 0.032f);
    // point light 2
    lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
    lightingShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    lightingShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    lightingShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    lightingShader.setFloat("pointLights[1].constant", 1.0f);
    lightingShader.setFloat("pointLights[1].linear", 0.09f);
    lightingShader.setFloat("pointLights[1].quadratic", 0.032f);
    // point light 3
    lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
    lightingShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
    lightingShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
    lightingShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
    lightingShader.setFloat("pointLights[2].constant", 1.0f);
    lightingShader.setFloat("pointLights[2].linear", 0.09f);
    lightingShader.setFloat("pointLights[2].quadratic", 0.032f);
    // point light 4
    lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
    lightingShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
    lightingShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
    lightingShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    lightingShader.setFloat("pointLights[3].constant", 1.0f);
    lightingShader.setFloat("pointLights[3].linear", 0.09f);
    lightingShader.setFloat("pointLights[3].quadratic", 0.032f);
    // spotLight
    lightingShader.setVec3("spotLight.position", glm::vec3(3.0f, 4.0f, 6.0f));
    lightingShader.setVec3("spotLight.direction", glm::vec3(0.0f, 0.0f, -1.0f));
    lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    lightingShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    lightingShader.setFloat("spotLight.constant", 1.0f);
    lightingShader.setFloat("spotLight.linear", 0.09f);
    lightingShader.setFloat("spotLight.quadratic", 0.032f);
    lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
}
