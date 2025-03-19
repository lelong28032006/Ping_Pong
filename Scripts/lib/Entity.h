//
// Created by Long on 19/03/2025.
//

#ifndef ENTITY_H
#define ENTITY_H

#pragma once
#include "DEFS.h"
#include <SDL.h>
#include <SDL_image.h>

class Entity {
public:
    Entity(float srcX = 0, float srcY = 0, float srcW = 0, float srcH = 0, float desX = 0, float desY = 0, float desW = 0, float desH = 0, SDL_Texture* p_tex = NULL);
    virtual ~Entity();
    void clear();
    float getSrcX();
    float getSrcY();
    float getSrcW();
    float getSrcH();
    void setSrcX(float val);
    void setSrcY(float val);
    void setSrcW(float val);
    void setSrcH(float val);

    float getDesX();
    float getDesY();
    float getDesW();
    float getDesH();
    void setDesX(float val);
    void setDesY(float val);
    void setDesW(float val);
    void setDesH(float val);

    SDL_Texture* getTexture();
    void setTexture(SDL_Texture* newTex);
    SDL_RendererFlip getFlip();
    void setFlip(SDL_RendererFlip newFlip);
    SDL_Rect getSrcFrame();
    SDL_Rect getDestFrame();

protected:
    float srcX, srcY, srcW, srcH;
    float desX, desY, desW, desH;
    SDL_Rect srcFrame, destFrame;
    SDL_Texture* texture_;
    SDL_RendererFlip flip_;

};


#endif //ENTITY_H
