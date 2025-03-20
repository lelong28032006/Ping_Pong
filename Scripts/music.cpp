//
// Created by Long on 20/03/2025.
//

#include "lib/music.h"

using namespace std;

Mix_Music* Theme = NULL;
Mix_Chunk* Paddle_Hit = NULL;
Mix_Chunk* Get_HighScore = NULL;

bool init_Audio() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer Lỗi: %s\n", Mix_GetError());
        return false;
    }


    Paddle_Hit = Mix_LoadWAV("Music/Paddle hit.wav");
    if (!Paddle_Hit) {
        printf("Can't load Paddle Hit Sound! %s\n", Mix_GetError());
        return false;
    }

    Get_HighScore = Mix_LoadWAV("Music/Score Blink.wav");
    if (!Get_HighScore) {
        printf("Can't load High Score Sound! %s\n", Mix_GetError());
        return false;
    }

    return true;
}

void close_Audio() {
    Mix_FreeMusic(Theme);
    Mix_FreeChunk(Paddle_Hit);
    Mix_FreeChunk(Get_HighScore);
    Mix_CloseAudio();
    SDL_Quit();
}

void Play_Theme_Music() {
    Mix_PlayMusic(Theme, -1);
}

void Play_Paddle_Hit_Sound() {
    Mix_PlayChannel(-1, Paddle_Hit, 0);
}

void Play_Get_HighScore_Sound() {
    Mix_PlayChannel(-1, Get_HighScore, 0);
}
