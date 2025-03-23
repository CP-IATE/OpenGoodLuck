#pragma once
#include <string>

class Shader
{
public:
	unsigned int shaderProgram;
	unsigned int VAO;
	unsigned int VBO;

	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
private:
	std::string readShaderFile(const char* filename);
};