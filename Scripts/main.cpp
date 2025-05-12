#include <bits/stdc++.h>
#include "lib/DEFS.h"
#include "lib/BaseObject.h"
#include "lib/Player.h"
#include "lib/music.h"

using namespace std;
const char* WINDOW_TITLE = "Ping Pong Ching Chong";

BaseObject background;
BaseObject Line;
BaseObject Line2;
BaseObject Text;
BaseObject Present_Score;
BaseObject High_Score;
BaseObject Mode_1_Text;
BaseObject Mode_2_Text;
BaseObject Mode_3_Text;
BaseObject Pause_Text;
BaseObject Player1_win_round;
BaseObject Player2_win_round;
BaseObject Back_to_menu_text;
BaseObject Menu_Arrow;
Player ball;
Player base_ball;
Player base_ball2;
Player bullet;

int score = 0;
int highest_score = 0;
int player1_win_round = 0;
int player2_win_round = 0;


bool initData();
bool loadbackground();
void waitUntilKeyPressed();
void quitEvents(bool &quitGame, bool &otherFlag);
void resetRoundState();
void resetGame();
void close();


int main(int argc, char *argv[]) {
    if (!initData() || !loadbackground()) {
        return -1;
    }

    base_ball.loadIMG("Images/base(1).jpg", renderer);
    base_ball.getRect();
    base_ball.setRect(140, 500);

    base_ball2.loadIMG("Images/base(1).jpg", renderer);
    base_ball2.getRect();
    base_ball2.setRect(140, 80);

    ball.loadIMG("Images/ball(1).png", renderer);
    ball.getRect();
    ball.setRect(SCREEN_WIDTH / 2.0 - 10, SCREEN_HEIGHT / 2.0);

    Line.loadIMG("Images/Line.png", renderer);
    Line.getRect();
    Line.setRect(0, 500);

    Line2.loadIMG("Images/Line.png", renderer);
    Line2.getRect();
    Line2.setRect(0, 80);

    bullet.loadIMG("Images/bullet.png", renderer);
    bullet.getRect();

    Menu_Arrow.loadIMG("Images/Menu_Arrow.png", renderer);
    Menu_Arrow.getRect();
    Menu_Arrow.setRect(60, SCREEN_HEIGHT / 2.0 + 5);
    Mode_1_Text.loadText("Text/Retro Gaming.ttf", "1 PLAYER", renderer, 30);
    Mode_1_Text.getRect();
    Mode_1_Text.setRect(120, SCREEN_HEIGHT / 2.0);
    Mode_2_Text.loadText("Text/Retro Gaming.ttf", "YOU v BOT", renderer, 30);
    Mode_2_Text.getRect();
    Mode_2_Text.setRect(120, SCREEN_HEIGHT / 2.0 + 60);
    Mode_3_Text.loadText("Text/Retro Gaming.ttf", "2 PLAYER", renderer, 30);
    Mode_3_Text.getRect();
    Mode_3_Text.setRect(120, SCREEN_HEIGHT / 2.0 + 120);
    Pause_Text.loadText("Text/Retro Gaming.ttf", "PAUSE", renderer, 30);
    Pause_Text.getRect();
    Pause_Text.setRect(140, SCREEN_HEIGHT / 2.0);
    Back_to_menu_text.loadText("Text/Retro Gaming.ttf", "PRESS SPACE: MENU", renderer, 12);
    Back_to_menu_text.getRect();
    Back_to_menu_text.setRect(125, SCREEN_HEIGHT / 2.0 + 60);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_Rect blackSquare1, blackSquare2; //Tạo hình vuông màu đen
    blackSquare1.x = 60;
    blackSquare1.y = SCREEN_HEIGHT / 2.0 + 5 + 60;
    blackSquare1.w = 30;
    blackSquare1.h = 30;

    blackSquare2.x = 60;
    blackSquare2.y = SCREEN_HEIGHT / 2.0 + 5 + 120;
    blackSquare2.w = 30;
    blackSquare2.h = 30;

    Present_Score.getRect();
    Present_Score.setRect(15, 15);

    High_Score.getRect();
    High_Score.setRect(15, 50);

    Player1_win_round.getRect();
    Player1_win_round.setRect(180, 10);

    Player2_win_round.getRect();
    Player2_win_round.setRect(180, 540);

    bool quitGame = false; // Thoát game
    int game_mode = 0;
    while (!quitGame) {
        bool menu = false; // Load Menu
        while (!menu) {
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    quitGame = true;
                    menu = true;  // Quit game luôn
                }
                if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_RETURN) {
                        Play_Select_Sound();
                        menu = true; // Ấn Enter để chọn chế độ
                    }
                    if (e.key.keysym.sym == SDLK_DOWN) {
                        if (game_mode == 1) {
                            blackSquare1.y = SCREEN_HEIGHT / 2.0 + 5;
                            blackSquare2.y = SCREEN_HEIGHT / 2.0 + 5 + 60;
                            Menu_Arrow.setRect(60, SCREEN_HEIGHT / 2.0 + 5 + 120);
                            game_mode = 2;
                            continue;
                        }
                        if (game_mode == 0) {
                            blackSquare1.y = SCREEN_HEIGHT / 2.0 + 5;
                            blackSquare2.y = SCREEN_HEIGHT / 2.0 + 5 + 120;
                            Menu_Arrow.setRect(60, SCREEN_HEIGHT / 2.0 + 5 + 60);
                            game_mode = 1;
                            continue;
                        }
                    }
                    if (e.key.keysym.sym == SDLK_UP) {
                        if (game_mode == 1) {
                            blackSquare1.y = SCREEN_HEIGHT / 2.0 + 5 + 60;
                            blackSquare2.y = SCREEN_HEIGHT / 2.0 + 5 + 120;
                            Menu_Arrow.setRect(60, SCREEN_HEIGHT / 2.0 + 5);
                            game_mode = 0;
                        }
                        if (game_mode == 2) {
                            blackSquare1.y = SCREEN_HEIGHT / 2.0 + 5;
                            blackSquare2.y = SCREEN_HEIGHT / 2.0 + 5 + 120;
                            Menu_Arrow.setRect(60, SCREEN_HEIGHT / 2.0 + 5 + 60);
                            game_mode = 1;
                        }
                    }
                }
            }
            Text.loadText("Text/Retro Gaming.ttf", "PING PONG", renderer, 40);
            Text.getRect();
            Text.setRect(70, 90);
            Text.Render(renderer);
            Mode_1_Text.Render(renderer);
            Mode_2_Text.Render(renderer);
            Mode_3_Text.Render(renderer);
            Menu_Arrow.Render(renderer);
            SDL_RenderFillRect(renderer, &blackSquare1);
            SDL_RenderFillRect(renderer, &blackSquare2);
            SDL_RenderPresent(renderer);
        }
        if (quitGame) break;
        if (game_mode == 0) {
            bool pause = false;
            bool mode_1_Playround = false;
            while (!mode_1_Playround) {
                resetGame(); // Reset thông số cho ván mới
                bool fistGet_Highest = false;

                bool begin = false;
                Uint32 lastToggleTime = SDL_GetTicks();
                bool showText = true;
                while (!begin) {
                    quitEvents(quitGame, begin); //Quit luôn Game
                    background.Render(renderer, NULL);
                    Line.Render(renderer, NULL);
                    base_ball.Render(renderer, NULL);
                    Present_Score.setScore(score, renderer, 4, 30);
                    Present_Score.Render(renderer, NULL);
                    High_Score.setScore(highest_score, renderer, 4, 30);
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
                if (quitGame || mode_1_Playround) break;

                bool quitRound = false; // Vòng lặp chính của 1 Player
                int lastSpeedUpScore = 0;
                while (!quitRound) {
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                            quitGame = true;
                            quitRound = true;
                        }
                        if (event.type == SDL_KEYDOWN) {
                            if (event.key.keysym.sym == SDLK_SPACE) {
                                pause = !pause;
                            }
                        }
                    }
                    while (pause) {
                        while (SDL_PollEvent(&event)) {
                            if (event.type == SDL_QUIT) {
                                quitGame = true;
                                quitRound = true;
                                pause = false;
                            }
                            if (event.type == SDL_KEYDOWN) {
                                pause = !pause;
                                if (event.key.keysym.sym == SDLK_SPACE) {
                                    mode_1_Playround = true;
                                    quitRound = true;
                                }
                            }
                        }
                        Pause_Text.Render(renderer);
                        SDL_RenderPresent(renderer);
                    }
                    if (Line.Cross_the_line(ball) || base_ball.Base_Touch(bullet)) {
                        quitRound = true;
                        break; // Ra khỏi vòng chơi chính
                    }

                    if (base_ball.Base_Touch(ball)) {
                        Play_Paddle_Hit_Sound();
                        ball.Rand_Angle();
                        ball.Bouncing(base_ball);
                        score++;
                        if (score > highest_score) {
                            highest_score = score;
                            if (fistGet_Highest == false) {
                                Play_Get_HighScore_Sound();
                                fistGet_Highest = true;
                            }
                        }
                    }
                    Present_Score.setScore(score, renderer, 4, 30);
                    High_Score.setScore(highest_score, renderer, 4, 30);
                    // Tăng tốc khi đạt điểm chia hết cho 10
                    if (score != 0 && score % 10 == 0 && score != lastSpeedUpScore && base_ball.Base_Touch(ball)) {
                        ball.SPEED_UP();
                        base_ball.SPEED_UP();
                        lastSpeedUpScore = score;
                    }
                    /*if (score != 0 && score % 5 == 0 && score != lastSpeedUpScore && base_ball.Base_Touch(ball)) {
                        bullet.SetRandom_Position();
                    }*/

                    /*if (bullet.Spawn_Bullet()) {
                        bullet.SetRandom_Position();
                    }*/

                    SDL_RenderClear(renderer);
                    background.Render(renderer, NULL);
                    Line.Render(renderer, NULL);
                    Present_Score.Render(renderer, NULL);
                    High_Score.Render(renderer, NULL);
                    base_ball.Render(renderer, NULL);
                    ball.Render(renderer, NULL);
                    /*if (score >= 5) {
                        bullet.Render(renderer, NULL);
                        bullet.Bullet_Move();
                    }*/
                    SDL_RenderPresent(renderer);

                    SDL_Delay(16);

                    if (score == 0) {
                        ball.Ball_START();
                        continue;
                    }

                    ball.Ball_Move();
                    base_ball.Player_Move();
                }
                if (quitGame || mode_1_Playround) break;

                bool waitForRestart = false;
                lastToggleTime = SDL_GetTicks();
                showText = true;
                while (!waitForRestart) {
                    SDL_Event e;
                    while (SDL_PollEvent(&e)) {
                        if (e.type == SDL_QUIT) {
                            quitGame = true; // Quit luôn Game
                            waitForRestart = true;
                        }
                        if (e.type == SDL_KEYDOWN) {
                            if (e.key.keysym.sym == SDLK_SPACE) {
                                mode_1_Playround = true;
                            }
                            waitForRestart = true;
                        }
                    }
                    background.Render(renderer, NULL);
                    Line.Render(renderer, NULL);
                    base_ball.Render(renderer, NULL);
                    ball.Render(renderer, NULL);
                    Present_Score.setScore(score, renderer, 4, 30);
                    Present_Score.Render(renderer, NULL);
                    High_Score.setScore(highest_score, renderer, 4, 30);
                    High_Score.Render(renderer, NULL);
                    Back_to_menu_text.Render(renderer, NULL);

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
                if (quitGame || mode_1_Playround) break;
            }
            SDL_RenderClear(renderer);
        }
        if (game_mode == 1) {
            bool pause = false;
            bool mode_2_Playround = false;
            while (!mode_2_Playround) {
                if (player1_win_round == 3 || player2_win_round == 3) resetGame(); //Reset thông số cho ván mới
                resetRoundState();
                bool begin = false;
                Uint32 lastToggleTime = SDL_GetTicks();
                bool showText = true;
                while (!begin) {
                    quitEvents(quitGame, begin); //Quit luôn Game
                    background.Render(renderer, NULL);
                    Line.Render(renderer, NULL);
                    Line2.Render(renderer, NULL);
                    base_ball.Render(renderer, NULL);
                    base_ball2.Render(renderer, NULL);
                    Player1_win_round.setScore(player1_win_round, renderer, 1, 40);
                    Player2_win_round.setScore(player2_win_round, renderer, 1, 40);
                    Player1_win_round.Render(renderer, NULL);
                    Player2_win_round.Render(renderer, NULL);

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
                if (quitGame || mode_2_Playround) break;
                bool quitRound = false; // Vòng lặp chính của You v Bot
                bool start = true;
                int count_touch = 0;
                int last_speed_up = 0;
                while (!quitRound) {
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                            quitGame = true;
                            quitRound = true;
                        }
                        if (event.type == SDL_KEYDOWN) {
                            if (event.key.keysym.sym == SDLK_SPACE) {
                                pause = !pause;
                            }
                        }
                    }
                    while (pause) {
                        while (SDL_PollEvent(&event)) {
                            if (event.type == SDL_QUIT) {
                                quitGame = true;
                                quitRound = true;
                                pause = false;
                            }
                            if (event.type == SDL_KEYDOWN) {
                                pause = !pause;
                                if (event.key.keysym.sym == SDLK_SPACE) {
                                    mode_2_Playround = true;
                                    quitRound = true;
                                }
                            }
                        }
                        Pause_Text.Render(renderer);
                        SDL_RenderPresent(renderer);
                    }
                    if (Line.Cross_the_line(ball)) {
                        player1_win_round++;
                        Play_Get_HighScore_Sound();
                        break; // Ra khỏi vòng chơi chính
                    }
                    if (Line2.Cross_the_top_line(ball)) {
                        player2_win_round++;
                        Play_Get_HighScore_Sound();
                        break; // Ra khỏi vòng chơi chính
                    }
                    if (base_ball.Base_Touch(ball)) {
                        Play_Paddle_Hit_Sound();
                        ball.Rand_Angle();
                        ball.Bouncing(base_ball);
                    }
                    if (base_ball2.Base_Touch(ball)) {
                        Play_Paddle_Hit_Sound();
                        ball.Bouncing(base_ball2);
                    }
                    Player1_win_round.setScore(player1_win_round, renderer, 1, 40);
                    Player2_win_round.setScore(player2_win_round, renderer, 1, 40);

                    SDL_RenderClear(renderer);
                    background.Render(renderer, NULL);
                    Line.Render(renderer, NULL);
                    Line2.Render(renderer, NULL);
                    Player1_win_round.Render(renderer, NULL);
                    Player2_win_round.Render(renderer, NULL);
                    base_ball.Render(renderer, NULL);
                    base_ball2.Render(renderer, NULL);
                    ball.Render(renderer, NULL);

                    SDL_RenderPresent(renderer);

                    SDL_Delay(16);

                    if (count_touch %10 == 0 && count_touch > 0 && count_touch != last_speed_up) {
                        last_speed_up = count_touch;
                        ball.SPEED_UP();
                    }

                    if (base_ball.Base_Touch(ball)) {
                        count_touch++;
                        start = false;
                    }
                    if (start) {
                        ball.Ball_START();
                        continue;
                    }

                    ball.Ball_Move();
                    base_ball.Player_Move();
                    base_ball2.Chasing(ball);
                }
                if (quitGame || mode_2_Playround) break;
                if (player1_win_round == 3 || player2_win_round == 3) {
                    if (player1_win_round == 3) {
                        Text.loadText("Text/Retro Gaming.ttf", "YOU LOSE!!!", renderer, 40);
                        Text.getRect();
                        Text.setRect(65, SCREEN_HEIGHT / 2.0 - 50);
                    }
                    else if (player2_win_round == 3) {
                        Text.loadText("Text/Retro Gaming.ttf", "YOU WIN!!!", renderer, 40);
                        Text.getRect();
                        Text.setRect(75, SCREEN_HEIGHT / 2.0 - 50);
                    }
                    bool waitForRestart = false;
                    while (!waitForRestart) {
                        SDL_Event e;
                        while (SDL_PollEvent(&e)) {
                            if (e.type == SDL_QUIT) {
                                quitGame = true; // Quit luôn Game
                                waitForRestart = true;
                            }
                            if (e.type == SDL_KEYDOWN) {
                                if (e.key.keysym.sym == SDLK_SPACE) {
                                    mode_2_Playround = true;
                                }
                                waitForRestart = true;
                            }
                        }
                        SDL_RenderClear(renderer);
                        background.Render(renderer, NULL);
                        Line.Render(renderer, NULL);
                        Line2.Render(renderer, NULL);
                        Player1_win_round.setScore(player1_win_round, renderer, 1, 40);
                        Player2_win_round.setScore(player2_win_round, renderer, 1, 40);
                        Player1_win_round.Render(renderer, NULL);
                        Player2_win_round.Render(renderer, NULL);
                        base_ball.Render(renderer, NULL);
                        base_ball2.Render(renderer, NULL);
                        Text.Render(renderer, NULL);
                        Back_to_menu_text.Render(renderer, NULL);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(16);
                    }
                }
                if (quitGame || mode_2_Playround) break;
            }
            SDL_RenderClear(renderer);
        }
        if (game_mode == 2) {
            bool pause = false;
            bool mode_3_Playround = false;
            while (!mode_3_Playround) {
                if (player1_win_round == 3 || player2_win_round == 3) resetGame(); //Reset thông số cho ván mới
                resetRoundState();
                bool begin = false;
                Uint32 lastToggleTime = SDL_GetTicks();
                bool showText = true;
                while (!begin) {
                    quitEvents(quitGame, begin); // Quit luôn Game
                    background.Render(renderer, NULL);
                    Line.Render(renderer, NULL);
                    Line2.Render(renderer, NULL);
                    base_ball.Render(renderer, NULL);
                    base_ball2.Render(renderer, NULL);
                    Player1_win_round.setScore(player1_win_round, renderer, 1, 40);
                    Player2_win_round.setScore(player2_win_round, renderer, 1, 40);
                    Player1_win_round.Render(renderer, NULL);
                    Player2_win_round.Render(renderer, NULL);

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
                if (quitGame || mode_3_Playround) break;
                bool quitRound = false; // Vòng lặp chính của 2 Player
                bool start = true;
                int count_touch = 0;
                int last_speed_up = 0;
                while (!quitRound) {
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                            quitGame = true;
                            quitRound = true;
                        }
                        if (event.type == SDL_KEYDOWN) {
                            if (event.key.keysym.sym == SDLK_SPACE) {
                                pause = !pause;
                            }
                        }
                    }
                    while (pause) {
                        while (SDL_PollEvent(&event)) {
                            if (event.type == SDL_QUIT) {
                                quitGame = true;
                                quitRound = true;
                                pause = false;
                            }
                            if (event.type == SDL_KEYDOWN) {
                                pause = !pause;
                                if (event.key.keysym.sym == SDLK_SPACE) {
                                    mode_3_Playround = true;
                                    quitRound = true;
                                }
                            }
                        }
                        Pause_Text.Render(renderer);
                        SDL_RenderPresent(renderer);
                    }
                    if (Line.Cross_the_line(ball)) {
                        player1_win_round++;
                        Play_Get_HighScore_Sound();
                        break; // Ra khỏi vòng chơi chính
                    }
                    if (Line2.Cross_the_top_line(ball)) {
                        player2_win_round++;
                        Play_Get_HighScore_Sound();
                        break; // Ra khỏi vòng chơi chính
                    }
                    if (base_ball.Base_Touch(ball)) {
                        Play_Paddle_Hit_Sound();
                        ball.Rand_Angle();
                        ball.Bouncing(base_ball);
                    }
                    if (base_ball2.Base_Touch(ball)) {
                        Play_Paddle_Hit_Sound();
                        ball.Bouncing(base_ball2);
                    }
                    Player1_win_round.setScore(player1_win_round, renderer, 1, 40);
                    Player2_win_round.setScore(player2_win_round, renderer, 1, 40);

                    SDL_RenderClear(renderer);
                    background.Render(renderer, NULL);
                    Line.Render(renderer, NULL);
                    Line2.Render(renderer, NULL);
                    Player1_win_round.Render(renderer, NULL);
                    Player2_win_round.Render(renderer, NULL);
                    base_ball.Render(renderer, NULL);
                    base_ball2.Render(renderer, NULL);
                    ball.Render(renderer, NULL);

                    SDL_RenderPresent(renderer);

                    SDL_Delay(16);

                    if (count_touch %5 == 0 && count_touch > 0 && count_touch != last_speed_up) {
                        last_speed_up = count_touch;
                        ball.SPEED_UP();
                    }

                    if (base_ball.Base_Touch(ball)) {
                        count_touch++;
                        start = false;
                    }
                    if (start) {
                        ball.Ball_START();
                        continue;
                    }
                    ball.Ball_Move();
                    base_ball.Player_Move();
                    base_ball2.Player2_Move();
                }
                if (quitGame || mode_3_Playround) break;
                if (player1_win_round == 3 || player2_win_round == 3) {
                    if (player1_win_round == 3) {
                        Text.loadText("Text/Retro Gaming.ttf", "PLAYER 1 WIN", renderer, 40);
                        Text.getRect();
                        Text.setRect(35, SCREEN_HEIGHT / 2.0 - 50);
                    }
                    else if (player2_win_round == 3) {
                        Text.loadText("Text/Retro Gaming.ttf", "PLAYER 2 WIN", renderer, 40);
                        Text.getRect();
                        Text.setRect(35, SCREEN_HEIGHT / 2.0 - 50);
                    }
                    bool waitForRestart = false;
                    while (!waitForRestart) {
                        SDL_Event e;
                        while (SDL_PollEvent(&e)) {
                            if (e.type == SDL_QUIT) {
                                quitGame = true;
                                waitForRestart = true;
                            }
                            if (e.type == SDL_KEYDOWN) {
                                if (e.key.keysym.sym == SDLK_SPACE) {
                                    mode_3_Playround = true;
                                }
                                waitForRestart = true;
                            }
                        }//Quit luôn Game
                        SDL_RenderClear(renderer);
                        background.Render(renderer, NULL);
                        Line.Render(renderer, NULL);
                        Line2.Render(renderer, NULL);
                        Player1_win_round.setScore(player1_win_round, renderer, 1, 40);
                        Player2_win_round.setScore(player2_win_round, renderer, 1, 40);
                        Player1_win_round.Render(renderer, NULL);
                        Player2_win_round.Render(renderer, NULL);
                        base_ball.Render(renderer, NULL);
                        base_ball2.Render(renderer, NULL);
                        Text.Render(renderer, NULL);
                        Back_to_menu_text.Render(renderer, NULL);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(16);
                    }
                }
                if (quitGame || mode_3_Playround) break;
            }
            SDL_RenderClear(renderer);
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

void resetRoundState() {
    base_ball.setRect(140, 500); //Reset vị trí Paddle
    base_ball.Reset_SPEED();
    base_ball2.setRect(140, 80); //Reset vị trí Paddle
    base_ball2.Reset_SPEED();
    ball.setRect(SCREEN_WIDTH / 2.0 - 10, SCREEN_HEIGHT / 2.0); //Reset vị trí bóng
    ball.Reset_SPEED();
    ball.Ball_START(); //Bóng về trạng thái khởi động
}

void resetGame() {
    score = 0;
    player1_win_round = 0;
    player2_win_round = 0;
    resetRoundState();
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