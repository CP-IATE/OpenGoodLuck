#include "Figure.h"
#include <glad/glad.h>
#include <iostream>

Figure::Figure(float* vertices, size_t vertices_count) {
	vertices_ = vertices;
	vertices_count_ = vertices_count;
    VAO = NULL;
    VBO = NULL;
    pShader_ = nullptr;
}

void Figure::setupVertexObjects() {
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_count_, vertices_, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Figure::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    pShader_->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Figure::setShader(Shader* shader) {
    pShader_ = shader;
}

Figure::~Figure() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}