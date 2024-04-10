#pragma once
#include "Vector2D.h"
#include "Game.h"
#include "Collision.h"

const int ENE_WIDTH = 64;
const int ENE_HEIGHT = 64;
const int ENE_VEL = 1;

class Enemy1
{
public:

    Enemy1(int x, int y);

    ~Enemy1();

    void Update(Vector2D Target, SDL_Rect Camera);

    void LoadSpriteState(int& cntState, const int& State, const int& STATE);

    void Move(Vector2D Target);

    void Render();

    void Destroy();

    bool IsDestroy()
    {
        return checkDead;
    }

    float Health = 100;

    Collision getColli()
    {
        return *EnemyColli;
    }
    bool checkHealth = false;

    bool attack_enemy = false;

private:
    Vector2D PosEnemy;
    Vector2D VelEnemy;
    SDL_Texture* EnemyTexture;
    SDL_Rect srcRect;

    Collision* EnemyColli = new Collision(0, 0, 64, 64);
    bool checkDead = false;

    enum
{
    Ene_IDLE_1,
    Ene_MoveAndAttack_1,
    Ene_TakenDamage_1,
    Ene_Dead_1,
    Ene_Total_1
};

int IDLE_1 = 6, cnt_IDLE_1 = 0,
    MoveAndAttack_1 = 5, cnt_MoveAndAttack_1 = 0,
    TakenDamage_1 = 4, cnt_TakenDamage_1 = 0,
    Dead_1 = 7, cnt_Dead_1 = 0;

    SDL_Rect Sprite_1[Ene_Total_1][7];
    SDL_Rect Current_Ene_1;
    SDL_RendererFlip CheckEne_1 = SDL_FLIP_NONE;
};

class Enemy2
{



};
