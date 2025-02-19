void logErrorAndExit(const char* msg, const char* error);
SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE);
SDL_Renderer* createRenderer(SDL_Window* window);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
void drawSomething(SDL_Window* window, SDL_Renderer* renderer);
SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer);
void renderTexture(SDL_Texture *texture, int x, int y,
                   SDL_Renderer* renderer);



// Created by Long on 18/02/2025.
//

#ifndef DEFS_H
#define DEFS_H

#endif //DEFS_H
