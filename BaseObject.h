//
// Created by Long on 19/02/2025.
//

#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "DEFS.h"
using namespace std;

struct Vector2 {
    int x;
    int y;
};

class BaseObject
{
public:
    BaseObject();
    virtual ~BaseObject();
    Vector2 speed_;
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
    void Player_Move();
    bool Base_Touch(BaseObject something);
    void Ball_Move();
    void Bouncing();


    void Free();

protected:
    SDL_Texture* texture_;
    SDL_Rect rect_;
};

#endif //BASEOBJECT_H
