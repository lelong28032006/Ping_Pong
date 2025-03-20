//
// Created by Long on 20/03/2025.
//

#ifndef MUSIC_H
#define MUSIC_H

#include "DEFS.h"

extern Mix_Music* Theme;
extern Mix_Chunk* Paddle_Hit;
extern Mix_Chunk* Get_HighScore;

bool init_Audio();
void close_Audio();
void Play_Theme_Music();
void Play_Paddle_Hit_Sound();
void Play_Get_HighScore_Sound();

#endif //MUSIC_H
