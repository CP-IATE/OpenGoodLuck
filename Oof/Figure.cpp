#include "Figure.h"
#include <glad/glad.h>
#include <iostream>

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

void Figure::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    pShader_->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices_count_, GL_UNSIGNED_INT, 0);
}

void Figure::setShader(Shader* shader) {
    pShader_ = shader;
}

Figure::~Figure() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBO);
}