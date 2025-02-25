#include <bits/stdc++.h>
#include "DEFS.h"
#include "BaseObject.h"
using namespace std;
const char* WINDOW_TITLE = "Ping Pong Game";

BaseObject background;
BaseObject ball;
BaseObject base_ball;

bool initData() {
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return false;
    }
    else {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) {
            printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
            return false;
        }
        else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            int imgFlag = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlag) && imgFlag)) {
                success = false;
            }
        }
    }
    return success;
}

bool loadbackground() {
    bool ret = background.loadIMG("Images/black.jpg", renderer);
    if (ret == false) {
        return false;
    }
    return true;
}

void waitUntilKeyPressed() {
    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT)) {
            return;
        }
        SDL_Delay(100);
    }
}

void close() {
    background.Free();
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char *argv[]) {
    if (!initData() || !loadbackground()) {
        return -1;
    }

    base_ball.loadIMG("Images/base.jpg", renderer);
    base_ball.getRect();
    base_ball.setRect(340,500);

    ball.loadIMG("Images/ball(1).png", renderer);
    ball.getRect();
    ball.setRect(340,400);

    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }
        base_ball.Move();
        // Vẽ lại màn hình
        SDL_RenderClear(renderer);
        background.Render(renderer);
        base_ball.Render(renderer, NULL);
        ball.Render(renderer, NULL);
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    return 0;
}

