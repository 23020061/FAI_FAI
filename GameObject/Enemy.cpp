#include "Enemy.h"
#include "TextureManager.h"
#include "Game.h"
#include <bits/stdc++.h>


Enemy1::Enemy1(int x, int y)
{
    PosEnemy.x = x;
    PosEnemy.y = y;

    EnemyColli->UpdateX(PosEnemy.x);
    EnemyColli->UpdateY(PosEnemy.y);

    EnemyTexture = TextureManager::LoadTexture("Massacre Sprite Sheet.png");

    for(int i = 0; i < Ene_Total_1; i++)
    {
        int tmp;
        switch (i)
        {
        case 0:
            tmp = IDLE_1;
            break;
        case 1:
            tmp = MoveAndAttack_1;
            break;
        case 2:
            tmp = TakenDamage_1;
            break;
        case 3:
            tmp = Dead_1;
            break;
        default:
            break;
        }
        for(int j = 0; j < tmp; j++)
        {
            Sprite_1[i][j].x = ENE_WIDTH * j;
            Sprite_1[i][j].y = ENE_HEIGHT * i;
            Sprite_1[i][j].w = ENE_WIDTH;
            Sprite_1[i][j].h = ENE_HEIGHT;
        }
    }

}

void Enemy1::LoadSpriteState(int& cntState, const int& State, const int& STATE)
{
    int temp;
    temp = cntState;
    cnt_IDLE_1 = 0;
    cnt_MoveAndAttack_1 = 0;
    cnt_TakenDamage_1 = 0;
    cnt_Dead_1 = 0;
    cntState = temp;
    cntState++;
    if(cntState >= State) cntState = 0;
    Current_Ene_1 = Sprite_1[STATE][cntState];
}


void Enemy1::Update(Vector2D Target, SDL_Rect Camera)
{
    Move(Target);

    PosEnemy.x += VelEnemy.x;
    PosEnemy.y += VelEnemy.y;

    EnemyColli->UpdateX(PosEnemy.x);
    EnemyColli->UpdateY(PosEnemy.y);

    srcRect.x = PosEnemy.x - Camera.x;
    srcRect.y = PosEnemy.y - Camera.y;
    srcRect.w = ENE_WIDTH;
    srcRect.h = ENE_HEIGHT;
}

void Enemy1::Move(Vector2D Target)
{
    VelEnemy.x = 0;
    VelEnemy.y = 0;
    static int a = 0;
    Target.y += 32;

    //Health = (Target.x - PosEnemy.x);

    if(HealthEnemy > 0)
    {
        static int checkTakenDamage = 0;
        if(checkHealth == true)
        {
            LoadSpriteState(cnt_TakenDamage_1, TakenDamage_1, Ene_TakenDamage_1);
            if(checkTakenDamage == TakenDamage_1 - 1)
            {
                checkHealth = false;
                checkTakenDamage = 0;
            }
            checkTakenDamage++;
        }
    else
    {
        if(Target.x == PosEnemy.x && Target.y == PosEnemy.y )
        {
            attack_enemy = true;
            //LoadSpriteState(cnt_IDLE_1, IDLE_1, Ene_IDLE_1);
        }
        else
        {
            attack_enemy = false;
        //std::cout << '(' << Target.x << ';' << Target.y << ')' << ' ' <<'(' << PosEnemy.x << ';' << PosEnemy.y << ')' << '\n';

        if(Target.x != PosEnemy.x)
        {
            if(Target.x > PosEnemy.x)
        {
            CheckEne_1 = SDL_FLIP_HORIZONTAL;
            VelEnemy.x += ENE_VEL;
        }
        else if(Target.x < PosEnemy.x)
        {
            CheckEne_1 = SDL_FLIP_NONE;
            VelEnemy.x -= ENE_VEL;
        }
        else VelEnemy.x = 0;
        }
        if(Target.y != PosEnemy.y)
        {
            if(Target.y >= PosEnemy.y)
        {
            VelEnemy.y += ENE_VEL;
        }
            else if(Target.y < PosEnemy.y)
        {
            VelEnemy.y -= ENE_VEL;
        }
            else VelEnemy.y = 0;
        }
            LoadSpriteState(cnt_MoveAndAttack_1, MoveAndAttack_1, Ene_MoveAndAttack_1);
        }
    }
    }
    else
    {
        if(HealthEnemy <= 0)
        {
            LoadSpriteState(cnt_Dead_1, Dead_1, Ene_Dead_1);
        a++;
        if(a == Dead_1)
        {
            Destroy();
            a = 0;
            checkDead = true;
        }
        }
    }
}


void Enemy1::Render()
{
    SDL_RenderCopyEx(Game::Renderer, EnemyTexture, &Current_Ene_1, &srcRect, 0, NULL, CheckEne_1);

}

void Enemy1::Destroy()
{
    SDL_DestroyTexture(EnemyTexture);
    delete EnemyTexture;
}
