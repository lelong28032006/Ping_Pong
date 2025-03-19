//
// Created by Long on 19/02/2025.
//

#include "lib/BaseObject.h"
#include  <bits/stdc++.h>

using namespace std;

BaseObject::BaseObject() {
    texture_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
    speed_.x = 8.00f;
    speed_.y = 8.00f;
    score_ = 0;
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

bool BaseObject::loadText(char *s,char * word, SDL_Renderer *renderer, int size) {
    TTF_Font* loadFont = TTF_OpenFont(s, size);
    if (loadFont == NULL) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                       SDL_LOG_PRIORITY_ERROR,
                       "Failed to load font: %s", TTF_GetError());
        return false;
    }
    SDL_Color color = {255, 255, 255, 255};  // Màu trắng
    SDL_Texture* new_Texture = NULL;
    SDL_Surface* new_Surface = TTF_RenderText_Solid(loadFont, word, color);
    if (new_Surface == NULL) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                       SDL_LOG_PRIORITY_ERROR,
                       "Failed to create surface: %s", TTF_GetError());
        TTF_CloseFont(loadFont);
        return false;
    }
    new_Texture = SDL_CreateTextureFromSurface(renderer, new_Surface);
    if (new_Texture != NULL) {
        rect_.w = new_Surface->w;
        rect_.h = new_Surface->h;
    }
    SDL_FreeSurface(new_Surface);
    texture_ = new_Texture;

    return texture_ != NULL;
}

void BaseObject::setScore(int s, SDL_Renderer *renderer) {
    getRect();
    setRect(30, 30);
    score_ = s;
    string text = "";
    string a = to_string(score_);
    for (int i = 0; i < 5-a.length(); i++) {
        text += '0';
    }
    text += a;
    loadText("Text/Retro Gaming.ttf", (char*)text.c_str(), renderer, 30);
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

bool BaseObject::EndOfTheGame(BaseObject &ball) {
    if (rect_.y < ball.rect_.y + ball.rect_.h -1) {
        return true;
    }
    return false;
}

void BaseObject::START() {
    loadText("Text/Retro Gaming.ttf", "PRESS ANY KEY", renderer, 30);
    Render(renderer);
    SDL_RenderPresent(renderer);
}