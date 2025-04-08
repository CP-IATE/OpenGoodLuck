#include "Figure.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Figure::Figure(float* vertices, size_t vertices_count, GLuint* indices, GLsizei indices_count, float* colors, size_t colors_count) {
	vertices_ = vertices;
	vertices_count_ = vertices_count;
    indices_ = indices;
    indices_count_ = indices_count;
    colors_ = colors;
    colors_count_ = colors_count;
    VAO = 0;
    VBO[0] = 0;
    VBO[1] = 0;
    EBO = 0;
    pShader_ = nullptr;
}

void Figure::setupVertexObjects() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glGenBuffers(2, VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_count_, vertices_, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices_count_, indices_, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * colors_count_, colors_, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
}

void Figure::draw(int SCR_WIDTH, int SCR_HEIGHT) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glLineWidth(3.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    pShader_->use();
    // create transformations
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime() * 3.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::lookAt(
        glm::vec3(0.5f, 0.5f, 2.0f),  // Camera position
        glm::vec3(0.0f, 0.0f, 0.0f),  // Look at the origin
        glm::vec3(0.0f, 1.0f, 0.0f)   // Up vector (Y-axis)
    );
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    // retrieve the matrix uniform locations
    unsigned int modelLoc = glGetUniformLocation(pShader_->shaderProgram, "model");
    unsigned int viewLoc = glGetUniformLocation(pShader_->shaderProgram, "view");
    // pass them to the shaders (3 different ways)
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    pShader_->setMat4("projection", projection);

    glBindVertexArray(VAO);
    glDrawElements(GL_LINES, indices_count_, GL_UNSIGNED_INT, 0);
}

void Figure::setShader(Shader* shader) {
    pShader_ = shader;
}

Figure::~Figure() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBO);
}