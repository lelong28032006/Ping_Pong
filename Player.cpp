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

bool Player::Base_Touch(Player &something) {
    if (rect_.x + rect_.w >= something.rect_.x && rect_.x <= something.rect_.x + something.rect_.w &&
        rect_.y - something.rect_.h <= something.rect_.y && rect_.y + rect_.h >= something.rect_.y) {
        return true;
        }
    return false;
}

void Player::SPEED_UP() {
    if (speed_.y > 0) speed_.y += 2.00f;
    else speed_.y -= 2.00f;
    if (speed_.x > 0) speed_.x += 2.00f;
    else speed_.x -= 2.00f;
}