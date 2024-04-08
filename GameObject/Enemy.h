#pragma once
#include "Vector2D.h"
#include "Game.h"


class Enemy1
{
public:

    Enemy1(int x, int y);

    ~Enemy1();

    void Update(Vector2D Target);

    void LoadSpriteState(int& cntState, const int& State, const int& STATE);

    void Move(Vector2D Target);

    void Render();

private:
    Vector2D PosEnemy;
    Vector2D VelEnemy;
    SDL_Texture* EnemyTexture;
    SDL_Rect srcRect;

};

class Enemy2
{



};
