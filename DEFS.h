

// Created by Long on 18/02/2025.
//

#ifndef DEFS_H
#define DEFS_H


#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Event event;

//Screen
const int SCREEN_WIDTH = 540;
const int SCREEN_HEIGHT = 405;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

#endif //DEFS_H
