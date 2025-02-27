#include <bits/stdc++.h>
#include "DEFS.h"
#include "BaseObject.h"

using namespace std;
const char* WINDOW_TITLE = "Ping Pong Game";

BaseObject background;
BaseObject ball;
BaseObject base_ball;
BaseObject bullet;
BaseObject Line;
BaseObject Text;

int score = 0;



bool initData() {
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) {
        cout << "SDL_Init Error: " << SDL_GetError() << endl;
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        return false;
    }
    else {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) {
            cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
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
    if (TTF_Init() == -1) {
        cout << "TTF Init Failed: " << TTF_GetError() << endl;
        return false;
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
    base_ball.setRect(SCREEN_WIDTH / 2.0, 500);

    ball.loadIMG("Images/ball(1).png", renderer);
    ball.getRect();
    ball.setRect(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0);

    Line.loadIMG("Images/Line.png", renderer);
    Line.getRect();
    Line.setRect(0, 500);

    Text.getRect();
    Text.setRect(30, 30);


    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }
        if (Line.EndOfTheGame(ball)) {
            quit = true;
        }
        ball.Ball_Move();
        base_ball.Player_Move();
        if (base_ball.Base_Touch(ball)) {
            ball.Bouncing();
            score++;
            Text.setScore(score, renderer);
        }
        if (score != 0 && score % 20 == 0 && base_ball.Base_Touch(ball)) {
            ball.SPEED_UP();
            base_ball.SPEED_UP();
        }
        // Vẽ lại màn hình
        SDL_RenderClear(renderer);
        background.Render(renderer, NULL);
        Line.Render(renderer, NULL);
        Text.Render(renderer, NULL);
        base_ball.Render(renderer, NULL);
        ball.Render(renderer, NULL);
        bullet.Render(renderer, NULL);
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    return 0;
}

