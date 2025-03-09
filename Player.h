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
};

#endif //PLAYER_H
