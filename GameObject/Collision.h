#include "Game.h"

class Collision
{
public:

    Collision(int x, int y, int w, int h);

    SDL_Rect getCollisionBox()
    {
        return CollisionBox;
    }

    bool checkCollision(Collision a, Collision b);

    void Update(int x, int y);

private:

    SDL_Rect CollisionBox;

};
