#include "Collision.h"

Collision::Collision(int x, int y, int w, int h)
{
    CollisionBox.x = x;
    CollisionBox.y = y;
    CollisionBox.w = w;
    CollisionBox.h = h;
}


bool Collision::checkCollision( Collision b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = CollisionBox.x;
    rightA = CollisionBox.x + CollisionBox.w;
    topA = CollisionBox.y;
    bottomA = CollisionBox.y + CollisionBox.h;

    leftB = b.getCollisionBox().x;
    rightB = b.getCollisionBox().x + b.getCollisionBox().w;
    topB = b.getCollisionBox().y;
    bottomB = b.getCollisionBox().y + b.getCollisionBox().h;

   if( ( ( bottomA <= topB ) || ( topA >= bottomB ) || ( rightA <= leftB ) || ( leftA >= rightB ) ) )
    {
        return false;
    }

    return true;
}

void Collision::UpdateX(int x)
{
    CollisionBox.x = x;
}

void Collision::UpdateY(int y)
{
    CollisionBox.y = y;
}

void Collision::UpdateW(int w)
{
    CollisionBox.w = w;
}

void Collision::UpdateH(int h)
{
    CollisionBox.h = h;
}
