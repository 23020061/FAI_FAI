#pragma once

#include "Game.h"

class Collision
{
public:

    Collision(int x, int y, int w, int h);

    SDL_Rect getCollisionBox()
    {
        return CollisionBox;
    }

    bool checkCollision( Collision b);

    void UpdateX(int x);

    void UpdateY(int y);

    void UpdateW(int w);

    void UpdateH(int h);



private:

    SDL_Rect CollisionBox;

};
