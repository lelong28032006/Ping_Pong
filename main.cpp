#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "DEFS.h"

using namespace std;


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Hello World!";

// Created by Long on 18/02/2025.
//

int main(int argc, char *argv[]) {
    SDL_Window *window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer *renderer = createRenderer(window);
    SDL_Texture* background = loadTexture("Images/bikiniBottom.jpg", renderer);

    SDL_RenderCopy( renderer, background, NULL, NULL);

    SDL_RenderPresent(renderer);
    SDL_Texture* spongeBob = loadTexture("Images/Spongebob.png", renderer);
    renderTexture(spongeBob, 200, 200, renderer);

    SDL_Texture* damn = loadTexture("Images/450569875_352876414510371_7073470396677283877_n.jpg", renderer);
    renderTexture(damn, 30, 30, renderer);

    SDL_RenderPresent( renderer );
    waitUntilKeyPressed();

    SDL_DestroyTexture( spongeBob );
    spongeBob = NULL;
    SDL_DestroyTexture( damn );
    damn = NULL;
    SDL_DestroyTexture( background );
    background = NULL;

    quitSDL(window, renderer);

    return 0;
}

