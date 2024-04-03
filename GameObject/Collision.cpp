#include "Collision.h"

Collision::Collision(int x, int y, int w, int h)
{
    CollisionBox.x = x;
    CollisionBox.y = y;
    CollisionBox.w = w;
    CollisionBox.h = h;
}


bool Collision::checkCollision(Collision a, Collision b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.getCollisionBox().x;
    rightA = a.getCollisionBox().x + a.getCollisionBox().w;
    topA = a.getCollisionBox().y;
    bottomA = a.getCollisionBox().y + a.getCollisionBox().h;

    leftB = b.getCollisionBox().x;
    rightB = b.getCollisionBox().x + b.getCollisionBox().w;
    topB = b.getCollisionBox().y;
    bottomB = b.getCollisionBox().y + b.getCollisionBox().h;

    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    return true;
}

void Collision::Update(int x, int y)
{
    CollisionBox.x = x;
    CollisionBox.y = y;
}
