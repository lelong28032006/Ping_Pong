//
// Created by Long on 19/02/2025.
//

#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "DEFS.h"
using namespace std;

class BaseObject
{
public:
    BaseObject();
    virtual ~BaseObject();
    void setRect(const int& x, const int& y) {
        rect_.x = x;
        rect_.y = y;
    }
    SDL_Rect getRect() const {
        return rect_;
    }
    SDL_Texture* getTexture() const {
        return texture_;
    }
    bool loadIMG(char* s, SDL_Renderer* renderer);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Move();
    void Free();

protected:
    SDL_Texture* texture_;
    SDL_Rect rect_;
};

#endif //BASEOBJECT_H
