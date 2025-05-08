#include <SDL3/SDL.h>
#pragma once
class App 
{
public:
	int width, height;
	const char* title;
	SDL_Window* window;
	App(int width, int height, const char* title);
	int run();
};
void framebuffer_size_callback(int width, int height);