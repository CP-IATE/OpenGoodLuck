#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    GLuint id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    // mesh data
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture>      textures;

    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
    void Draw(Shader& shader);
private:
    //  render data
    GLuint VAO, VBO, EBO;

    void setupMesh();
};
