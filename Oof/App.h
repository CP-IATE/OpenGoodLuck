#pragma once
class App 
{
public:
	int width, height;
	const char* title;
	GLFWwindow* window;
	App(int width, int height, const char* title);
	int run();
};
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);