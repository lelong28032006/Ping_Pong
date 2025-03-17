//
// Created by Long on 09/03/2025.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "BaseObject.h"

using namespace std;

class Player : public BaseObject {
    public:
    Player();
    virtual ~Player();
    void Player_Move();
    bool Base_Touch(Player& somthing);
    void SPEED_UP();
    void Bouncing();
    void Ball_Move();
    void Ball_START();
    void Reset_SPEED();
    void SetRandom_Position();
    void Bullet_Move();
    bool Spawn_Bullet();
};

#endif //PLAYER_H
