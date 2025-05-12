#pragma once
struct GLFWwindow;

class Engine
{
public:
	int run();
    void PollEvents(bool& running);

private:
    static constexpr const char* VERTEX_SHADER_PATH = "./shaders/vertex.glsl";
    static constexpr const char* FRAGMENT_SHADER_PATH = "./shaders/fragment.glsl";
    static constexpr const char* WINDOW_DISPLAY_NAME = "Cubey spinning thing";
    static constexpr const char* AUDIO_FILE = "funkytown.mp3";
    static constexpr const char* PEAK_MODEL = "models/cubey.obj";
};

class Shader;

void rotateView(Shader& shader);
