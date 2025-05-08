#include "Music.h"
#include <iostream>

Music::Music(const char* music_path)
    : music_source(music_path), engine{}, sound{}, initialized(false)
{
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        std::cout << "ERROR::SOUND::ENGINE::INITIALIZATION_FAILED\nERROR CODE: " << result << std::endl;
        return;
    }

    result = ma_sound_init_from_file(&engine, music_source.c_str(), 0, NULL, NULL, &sound);
    if (result != MA_SUCCESS) {
        std::cout << "ERROR::SOUND::FILE::INITIALIZATION_FAILED\nERROR CODE: " << result << std::endl;
        ma_engine_uninit(&engine);
        return;
    }

    initialized = true;
}

void Music::start() {
    if (initialized)
        ma_sound_start(&sound);
}

void Music::end() {
    if (initialized) {
        ma_sound_uninit(&sound);
        ma_engine_uninit(&engine);
    }
}
