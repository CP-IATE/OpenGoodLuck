#ifndef SHADER_H
#define SHADER_H
#include <string>


class Shader 
{
public:
	unsigned int shaderProgram, VAO, VBO;

	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
private:
	std::string readShaderFile(const char* filename);
};

#endif // SHADER_H

