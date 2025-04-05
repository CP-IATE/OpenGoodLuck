#pragma once
#include "Shader.h"

class Figure
{
public:
	GLuint VAO, VBO[2]; //Vertex objects
	GLuint EBO;

	Figure(float* vertices, size_t vertices_count, GLuint* indices, GLsizei indices_count, float* colors, size_t colors_count);
	void setupVertexObjects();
	void draw();
	void setShader(Shader* shader);
	~Figure();
private:
	float* vertices_;
	GLuint* indices_;
	float* colors_;
	size_t vertices_count_, indices_count_, colors_count_;
	Shader* pShader_;
};

