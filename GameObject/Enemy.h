#pragma once
#include "Vector2D.h"
#include "Game.h"
#include "Collision.h"

const int ENE_WIDTH = 64;
const int ENE_HEIGHT = 64;
const int ENE_VEL = 3;


class Enemy1
{
public:

    Enemy1(int x, int y);

    ~Enemy1();

    void Update(Vector2D Target,Collision temp, SDL_Rect Camera);

    void LoadSpriteState(int& cntState, const int& State, const int& STATE);

    void Move(Vector2D Target, Collision temp);

    void Render();

    void Destroy();

    bool IsDestroy()
    {
        return checkDead;
    }

    float HealthEnemy = 5;

    Collision getColli()
    {
        return *EnemyColli;
    }
    bool checkHealth = false;

    bool attack_enemy = false;


        enum
{
    Ene_IDLE_1 = 0,
    Ene_MoveAndAttack_1 = 1,
    Ene_TakenDamage_1 = 2,
    Ene_Dead_1 = 3,
    Ene_Total_1 = 4
};

int IDLE_1 = 6, cnt_IDLE_1 = 0,
    MoveAndAttack_1 = 5, cnt_MoveAndAttack_1 = 0,
    TakenDamage_1 = 4, cnt_TakenDamage_1 = 0,
    Dead_1 = 7, cnt_Dead_1 = 0;

    SDL_Rect Sprite_1[Ene_Total_1][7];
    SDL_Rect Current_Ene_1;
    SDL_RendererFlip CheckEne_1 = SDL_FLIP_NONE;


private:
    Vector2D PosEnemy;
    Vector2D VelEnemy;
    SDL_Texture* EnemyTexture;
    SDL_Rect srcRect;

    Collision* EnemyColli = new Collision(0, 0, 64, 64);
    bool checkDead = false;

    int a = 0;


};

class Enemy2
{
public:

//new


};
