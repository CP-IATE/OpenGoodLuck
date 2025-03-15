#ifndef ENGINE_H
#define ENGINE_H

struct GLFWwindow;

class Engine 
{
public:
	int run();
	void processInput(GLFWwindow* window);
};

#endif // ENGINE_H
