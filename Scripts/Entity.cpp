//
// Created by Long on 19/03/2025.
//

#include "lib/Entity.h"

#include <bits/stdc++.h>

using namespace std;

Entity::Entity(float srcX, float srcY, float srcW, float srcH, float desX, float desY, float desW, float desH, SDL_Texture* newTexture)
:srcX(srcX), srcY(srcY), srcW(srcW), srcH(srcH), desX(desX), desY(desY), desW(desW), desH(desH), texture_(newTexture)
{
    flip_ = SDL_FLIP_NONE;

    srcFrame.x = srcX;
    srcFrame.y = srcY;
    srcFrame.w = srcW;
    srcFrame.h = srcH;

    destFrame.x = desX;
    destFrame.y = desY;
    destFrame.w = desW;
    destFrame.h = desH;

}

Entity::~Entity() {

}

void Entity::clear()
{
     setTexture(NULL);
     setSrcX(0); setSrcY(0); setSrcW(0); setSrcH(0);
     setDesX(0); setDesY(0); setDesW(0); setDesH(0);
     setFlip(SDL_FLIP_NONE);
}
float Entity::getSrcX()
{
    return srcX;
}

float Entity::getSrcY()
{
    return srcY;
}

float Entity::getSrcW()
{
    return srcW;
}

float Entity::getSrcH()
{
    return srcH;
}

float Entity::getDesX()
{
    return desX;
}

float Entity::getDesY()
{
    return desY;
}

float Entity::getDesW()
{
    return desW;
}

float Entity::getDesH()
{
    return desH;
}

void Entity::setSrcX(float val)
{
    srcX = val;
    srcFrame.x = srcX;
}

void Entity::setSrcY(float val)
{
    srcY = val;
    srcFrame.y = srcY;
}

void Entity::setSrcW(float val)
{
    srcW = val;
    srcFrame.w = srcW;
}

void Entity::setSrcH(float val)
{
    srcH = val;
    srcFrame.h = srcH;
}

void Entity::setDesX(float val)
{
    desX = val;
    destFrame.x = desX;
}

void Entity::setDesY(float val)
{
    desY = val;
    destFrame.y = desY;
}

void Entity::setDesW(float val)
{
    desW = val;
    destFrame.w = desW;
}

void Entity::setDesH(float val)
{
    desH = val;
    destFrame.h = desH;
}

SDL_RendererFlip Entity::getFlip()
{
    return flip_;
}

void Entity::setFlip(SDL_RendererFlip newFlip)
{
    flip_ = newFlip;
}

SDL_Texture* Entity::getTexture()
{
    return texture_;
}

void Entity::setTexture(SDL_Texture *newTex)
{
    texture_ = newTex;
}

SDL_Rect Entity::getSrcFrame()
{
    return srcFrame;
}

SDL_Rect Entity::getDestFrame()
{
    return destFrame;
}


