//
// Created by Long on 19/02/2025.
//

#include "BaseObject.h"
#include  <bits/stdc++.h>

using namespace std;

BaseObject::BaseObject() {
    texture_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

BaseObject::~BaseObject() {

}

bool BaseObject::loadIMG(char *s, SDL_Renderer *renderer) {
    SDL_Texture* new_Texture = NULL;
    SDL_Surface* new_Surface = IMG_Load(s);

    if (new_Surface != NULL) {
        SDL_SetColorKey(new_Surface, SDL_TRUE, SDL_MapRGB(new_Surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        new_Texture = SDL_CreateTextureFromSurface(renderer, new_Surface);
        if (new_Texture != NULL) {
            rect_.w = new_Surface->w;
            rect_.h = new_Surface->h;
        }
        SDL_FreeSurface(new_Surface);
    }
    texture_ = new_Texture;

    return texture_ != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip) {
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};
    SDL_RenderCopy(des, texture_, clip, &renderquad);
}

void BaseObject::Free() {
    if (texture_ != NULL) {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}
void BaseObject::Move() {
    int base_x = rect_.x;
    int base_y = rect_.y;
    const int base_SPEED = 10;
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

