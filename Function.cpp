#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "DEFS.h"

using namespace std;


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


void logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE)
{
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit( "SDL_image error:", IMG_GetError());
    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //full screen
    //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);

    return window;
}
SDL_Renderer* createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return renderer;
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
void drawSomething(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_Rect filled_rect;
    filled_rect.x = SCREEN_WIDTH-1000;
    filled_rect.y = SCREEN_HEIGHT-1000;
    filled_rect.w = 1000;
    filled_rect.h = 1000;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    SDL_RenderFillRect(renderer, &filled_rect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);   // red
    SDL_RenderDrawLine(renderer, 100, 100, 200, 200);
}

SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                     "Loading %s", filename);

    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "Load texture %s", IMG_GetError());
    }

    return texture;
}
void renderTexture(SDL_Texture *texture, int x, int y,
                   SDL_Renderer* renderer)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;

    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

// Created by Long on 19/02/2025.
//
