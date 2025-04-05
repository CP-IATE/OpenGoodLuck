#include <iostream>
#include <fstream>
#include <sstream>
#include "Shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    std::string vertexShaderSourcestr = readShaderFile(vertexShaderPath);
    std::string fragmentShaderSourcestr = readShaderFile(fragmentShaderPath);

    const char* vertexShaderSource = vertexShaderSourcestr.c_str();
    const char* fragmentShaderSource = fragmentShaderSourcestr.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkCompileErrors(shaderProgram, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() const
{
    glUseProgram(shaderProgram);
}


void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

std::string Shader::readShaderFile(const char* filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open shader file: " << filename << std::endl;
        return "";
    }

    std::stringstream ss{};
    ss << file.rdbuf();
    return ss.str();
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << type << "::LINKING_FAILED\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

Shader::~Shader() {
    glDeleteProgram(shaderProgram);
}