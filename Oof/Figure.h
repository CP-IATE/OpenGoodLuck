#pragma once
#include "Shader.h"

class Figure
{
public:
	unsigned int VAO, VBO[2]; //Vertex objects
	unsigned int EBO;

	Figure(float* vertices, size_t vertices_count, float* indices, size_t indices_count, float* colors, size_t colors_count);
	void setupVertexObjects();
	void draw();
	void setShader(Shader* shader);
	~Figure();
private:
	float* vertices_;
	float* indices_;
	float* colors_;
	size_t vertices_count_, indices_count_, colors_count_;
	Shader* pShader_;
};

