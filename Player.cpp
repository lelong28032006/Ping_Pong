//
// Created by Long on 09/03/2025.
//

#include "Player.h"
#include  <bits/stdc++.h>

using namespace std;

Player::Player() {

}

Player::~Player() {

}

void Player::Player_Move() {
    int base_x = rect_.x;
    int base_y = rect_.y;
    const int base_SPEED = speed_.x;
    const Uint8* keyStates = SDL_GetKeyboardState(NULL);
    if (keyStates[SDL_SCANCODE_LEFT]) {
        base_x -= base_SPEED;
        if (base_x < 0) base_x = 0; // Giữ paddle trong màn hình
    }
    if (keyStates[SDL_SCANCODE_RIGHT]) {
        base_x += base_SPEED;
        if (base_x > SCREEN_WIDTH - rect_.w)
            base_x = SCREEN_WIDTH - rect_.w;
    }

    rect_.x = base_x;
    rect_.y = base_y;
}