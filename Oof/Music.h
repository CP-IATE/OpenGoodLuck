#pragma once
#include <string>
#include "miniaudio.h"

class Music
{
public:
	Music(const char* music_path);
	void start();
	void end();
	std::string music_source;

private:
	ma_result result;
	ma_engine engine;
	ma_sound sound;
};