#include <bits/stdc++.h>
#include "lib/DEFS.h"
#include "lib/BaseObject.h"
#include "lib/Player.h"
#include "lib/music.h"

using namespace std;
const char* WINDOW_TITLE = "Ping Pong Ching Chong";

BaseObject background;
BaseObject Line;
BaseObject Text;
BaseObject Present_Score;
BaseObject High_Score;
Player ball;
Player base_ball;
Player bullet;

int score = 0;
int highest_score = 0;


bool initData();
bool loadbackground();
void waitUntilKeyPressed();
void quitEvents(bool &quitGame, bool &otherFlag);
void resetGame();
void close();


int main(int argc, char *argv[]) {
    if (!initData() || !loadbackground()) {
        return -1;
    }

    int lastSpeedUpScore = 0;

    base_ball.loadIMG("Images/base(1).jpg", renderer);
    base_ball.getRect();
    base_ball.setRect(140, 500);

    ball.loadIMG("Images/ball(1).png", renderer);
    ball.getRect();
    ball.setRect(SCREEN_WIDTH / 2.0 - 10, SCREEN_HEIGHT / 2.0);

    Line.loadIMG("Images/Line.png", renderer);
    Line.getRect();
    Line.setRect(0, 500);

    bullet.loadIMG("Images/bullet.png", renderer);
    bullet.getRect();

    Present_Score.getRect();
    Present_Score.setRect(15, 15);

    High_Score.getRect();
    High_Score.setRect(15, 50);

    bool quitGame = false; // Khi nào thật sự muốn thoát game

    while (!quitGame) {
        // Reset thông số cho ván mới
        resetGame();
        bool start_to_get_bullet = false; // Giá trị để quyết xem có render Bullet
        bool fistGet_Highest = false;

        bool begin = false;
        Uint32 lastToggleTime = SDL_GetTicks();
        bool showText = true;
        while (!begin) {
            quitEvents(quitGame, begin);//Quit luôn Game
            background.Render(renderer, NULL);
            Line.Render(renderer, NULL);
            base_ball.Render(renderer, NULL);
            Present_Score.setScore(score, renderer);
            Present_Score.Render(renderer, NULL);
            High_Score.setScore(highest_score, renderer);
            High_Score.Render(renderer, NULL);

            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - lastToggleTime >= 500) {
                showText = !showText;
                lastToggleTime = currentTime;
            }

            if (showText) {
                Text.loadText("Text/Retro Gaming.ttf", "PRESS ANY KEY", renderer, 30);
                Text.getRect();
                Text.setRect(65, SCREEN_HEIGHT / 2.0 - 50);
                Text.Render(renderer, NULL);
            }

            SDL_RenderPresent(renderer);

            SDL_Delay(16);
        }
        bullet.setRect(0, 0);
        if (quitGame) break;
        // Vòng lặp chính của game
        bool quitRound = false;
        while (!quitRound) {

            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    quitGame = true;
                    quitRound = true;
                }
            }

            if (Line.EndOfTheGame(ball) || base_ball.Base_Touch(bullet)) {
                quitRound = true;
                break; // Ra khỏi vòng chơi chính
            }

            if (base_ball.Base_Touch(ball)) {
                Play_Paddle_Hit_Sound();
                ball.Bouncing();
                score++;
                if (score > highest_score) {
                    highest_score = score;
                    if (fistGet_Highest == false) {
                        Play_Get_HighScore_Sound();
                        fistGet_Highest = true;
                    }
                }
            }
            Present_Score.setScore(score, renderer);
            High_Score.setScore(highest_score, renderer);
            // Tăng tốc khi đạt điểm chia hết cho 10
            if (score != 0 && score % 10 == 0 && score != lastSpeedUpScore && base_ball.Base_Touch(ball)) {
                ball.SPEED_UP();
                base_ball.SPEED_UP();
                lastSpeedUpScore = score;
            }
            if (score != 0 && score % 5 == 0 && score != lastSpeedUpScore && base_ball.Base_Touch(ball)) {
                bullet.SetRandom_Position();
            }

            if (bullet.Spawn_Bullet()) {
                bullet.SetRandom_Position();
            }

            SDL_RenderClear(renderer);
            background.Render(renderer, NULL);
            Line.Render(renderer, NULL);
            Present_Score.Render(renderer, NULL);
            High_Score.Render(renderer, NULL);
            base_ball.Render(renderer, NULL);
            ball.Render(renderer, NULL);
            if (score >= 5) {
                bullet.Render(renderer, NULL);
                bullet.Bullet_Move();
            }
            SDL_RenderPresent(renderer);

            SDL_Delay(16);

            if (score == 0) {
                ball.Ball_START();
                continue;
            }

            ball.Ball_Move();
            base_ball.Player_Move();
        }


        if (quitGame) break;

        bool waitForRestart = false;
        lastToggleTime = SDL_GetTicks();
        showText = true;
        while (!waitForRestart) {
            quitEvents(quitGame, waitForRestart);//Quit luôn Game
            background.Render(renderer, NULL);
            Line.Render(renderer, NULL);
            base_ball.Render(renderer, NULL);
            ball.Render(renderer, NULL);
            Present_Score.setScore(score, renderer);
            Present_Score.Render(renderer, NULL);
            High_Score.setScore(highest_score, renderer);
            High_Score.Render(renderer, NULL);

            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - lastToggleTime >= 500) {
                showText = !showText;
                lastToggleTime = currentTime;
            }

            if (showText) {
                Text.loadText("Text/Retro Gaming.ttf", "TRY AGAIN!", renderer, 30);
                Text.getRect();
                Text.setRect(100, SCREEN_HEIGHT / 2.0 - 50);
                Text.Render(renderer, NULL);
            }

            SDL_RenderPresent(renderer);

            SDL_Delay(16);
        }

    }

    close();
    return 0;
}

bool initData() {
    bool success = true;
    //Render video
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
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int imgFlag = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlag) && imgFlag)) {
    success = false;
    //Render Text
    }
    if (TTF_Init() == -1) {
        cout << "TTF Init Failed: " << TTF_GetError() << endl;
        return false;
    }
    //Render Music
    if (!init_Audio()) {
        cout << "init_Audio Error: " << Mix_GetError() << endl;
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

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if  ( SDL_PollEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(10);
    }
}

void quitEvents(bool &quitGame, bool &otherFlag) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quitGame = true;
            otherFlag = true;  // Cho vòng lặp bên ngoài dừng lại luôn
        }
        if (e.type == SDL_KEYDOWN) {
            otherFlag = true;
        }
    }
}


void resetGame() {
    score = 0;
    base_ball.setRect(140, 500); // Reset vị trí thanh trượt
    base_ball.Reset_SPEED();
    ball.setRect(SCREEN_WIDTH / 2.0 - 10, SCREEN_HEIGHT / 2.0); // Reset vị trí bóng
    ball.Reset_SPEED();
    ball.Ball_START();            // Khởi động lại bóng
}


void close() {
    background.Free();
    close_Audio(); // Đóng âm thanh trước khi quit SDL
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    IMG_Quit();
    SDL_Quit();
}



/*
// FLAPPY
#include <SDL.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 600;
const int BIRD_WIDTH = 20;
const int BIRD_HEIGHT = 20;
const int PIPE_WIDTH = 50;
const int PIPE_GAP = 150;

class Bird {
public:
    int x, y, velocity;

    Bird() {
        x = 50;
        y = SCREEN_HEIGHT / 2;
        velocity = 0;
    }

    void jump() {
        velocity = -100;
    }

    void update() {
        velocity += 1; // Gravity
        y += velocity;
    }

    void draw(SDL_Renderer* renderer) {
        SDL_Rect birdRect = { x, y, BIRD_WIDTH, BIRD_HEIGHT };
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &birdRect);
    }
};

class Pipe {
public:
    int x, height;

    Pipe() {
        x = SCREEN_WIDTH;
        height = rand() % (SCREEN_HEIGHT - PIPE_GAP - 100) + 50; // Random height
    }

    void update() {
        x -= 5; // Move left
    }

    void draw(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_Rect topPipe = { x, 0, PIPE_WIDTH, height };
        SDL_Rect bottomPipe = { x, height + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT - height - PIPE_GAP };
        SDL_RenderFillRect(renderer, &topPipe);
        SDL_RenderFillRect(renderer, &bottomPipe);
    }
};

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Flappy Bird Clone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    Bird bird;
    std::vector<Pipe> pipes;
    pipes.push_back(Pipe());

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    bird.jump();
                }
            }
        }

        bird.update();

        if (pipes.back().x < SCREEN_WIDTH - 200) {
            pipes.push_back(Pipe());
        }

        for (auto& pipe : pipes) {
            pipe.update();
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw bird
        bird.draw(renderer);

        // Draw pipes
        for (auto& pipe : pipes) {
            pipe.draw(renderer);
        }

        // Present the back buffer
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}*/