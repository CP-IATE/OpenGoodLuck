#pragma once
#include "Shader.h"

class Figure
{
public:
	unsigned int VAO, VBO; //Vertex objects

	Figure(float* vertices, size_t vertices_count);
	void setupVertexObjects();
	void draw();
	void setShader(Shader* shader);
	~Figure();
private:
	float* vertices_;
	size_t vertices_count_;
	Shader* pShader_;
};

