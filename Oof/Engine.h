#pragma once
struct GLFWwindow;

class Engine
{
public:
	int run();

private:
    static constexpr const char* VERTEX_SHADER_PATH = "./shaders/vertex.glsl";
    static constexpr const char* FRAGMENT_SHADER_PATH = "./shaders/fragment.glsl";
    static constexpr const char* WINDOW_DISPLAY_NAME = "Cubey spinning thing";
};