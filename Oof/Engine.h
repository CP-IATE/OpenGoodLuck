#pragma once
struct GLFWwindow;

class Engine
{
public:
	int run();
	void processInput(GLFWwindow* window);
};