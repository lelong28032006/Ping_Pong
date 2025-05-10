//
// Created by Long on 09/03/2025.
//

#include "lib/Player.h"
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
    /*if (keyStates[SDL_SCANCODE_SPACE]) {
        if (base_x + rect_.w/2 < SCREEN_WIDTH/2) {
            base_x = SCREEN_WIDTH - rect_.w;
        }
        if (base_x + rect_.w/2 >= SCREEN_WIDTH/2) {
            base_x = 0;
        }
    }*/

    rect_.x = base_x;
    rect_.y = base_y;
}

void Player::Player2_Move() {
    int base_x = rect_.x;
    int base_y = rect_.y;
    const int base_SPEED = speed_.x;
    const Uint8* keyStates = SDL_GetKeyboardState(NULL);
    if (keyStates[SDL_SCANCODE_A]) {
        base_x -= base_SPEED;
        if (base_x < 0) base_x = 0; // Giữ paddle trong màn hình
        //cout << "A" << endl;
    }
    if (keyStates[SDL_SCANCODE_D]) {
        base_x += base_SPEED;
        if (base_x > SCREEN_WIDTH - rect_.w)
            base_x = SCREEN_WIDTH - rect_.w;
        //cout << "D" << endl;
    }
    if (keyStates[SDL_SCANCODE_SPACE]) {
        if (base_x + rect_.w/2 < SCREEN_WIDTH/2) {
            base_x = SCREEN_WIDTH - rect_.w;
        }
        if (base_x + rect_.w/2 >= SCREEN_WIDTH/2) {
            base_x = 0;
        }
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

void Player::Ball_Move() {
    rect_.x += speed_.x;
    rect_.y += speed_.y;
    if (rect_.x >= SCREEN_WIDTH - rect_.w || rect_.x <= 0) {
        speed_.x *= -1;
    }
    if (rect_.y >= SCREEN_HEIGHT - rect_.h || rect_.y <= 0) {
        speed_.y *= -1;
    }
}

void Player::Rand_Angle() {
    random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<float> dist(-1.00f, 1.00f);
    speed_.x += dist(gen);
}

void Player::Bouncing(Player &Base) {
    if (Base.rect_.x + Base.rect_.w >= rect_.x && Base.rect_.x <= rect_.x + rect_.w) {
        speed_.y *= -1;
    }
    else if (Base.rect_.y - rect_.h <= rect_.y && Base.rect_.y + Base.rect_.h >= rect_.y) {
        speed_.x *= -1;
    }
}

void Player::Reset_SPEED() {
    speed_.x = 8.00f;
    speed_.y = 8.00f;
}

void Player::Ball_START() {
    rect_.x = rect_.x + 0;
    rect_.y += speed_.y;
}

void Player::SetRandom_Position() {
    random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, SCREEN_WIDTH - rect_.w);
    rect_.x = dist(gen);
    rect_.y = 0;
}

void Player::Bullet_Move() {
    rect_.y += speed_.y-2.00f;
}

bool Player::Spawn_Bullet() {
    if (rect_.y >= SCREEN_HEIGHT) {
        return true;
    }
    return false;
}

void Player::Chasing(Player &something) {
    if (rect_.x + rect_.w/2 > something.rect_.x) {
        rect_.x -= speed_.x;
        if (rect_.x > SCREEN_WIDTH - rect_.w)
            rect_.x = SCREEN_WIDTH - rect_.w;
    }
    if (rect_.x + rect_.w/2 < something.rect_.x) {
        rect_.x += speed_.x;
        if (rect_.x < 0) rect_.x = 0; // Giữ paddle trong màn hình
    }
    if (rect_.x > SCREEN_WIDTH - rect_.w)
        rect_.x = SCREEN_WIDTH - rect_.w;
    if (rect_.x < 0) rect_.x = 0; // Giữ paddle trong màn hình
}
