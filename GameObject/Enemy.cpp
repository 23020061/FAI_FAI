#include "Enemy.h"
#include "TextureManager.h"
#include "Game.h"
#include <bits/stdc++.h>


Enemy1::Enemy1(int x, int y)
{
    PosEnemy.x = x;
    PosEnemy.y = y;

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
Enemy1::~Enemy1()
{
    SDL_DestroyTexture(EnemyTexture);
    delete EnemyColli;
    delete EnemyTexture;
}

void Enemy1::LoadSpriteState(int& cntState, const int& State, const int& STATE)
{
    int temp = 0;
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

void Enemy1::Update(Vector2D Target, Collision temp, SDL_Rect Camera)
{
    Move(Target, temp);

    PosEnemy.x += VelEnemy.x;
    PosEnemy.y += VelEnemy.y;

    EnemyColli->UpdateX(PosEnemy.x);
    EnemyColli->UpdateY(PosEnemy.y + 40);
    EnemyColli->UpdateH(24);
    EnemyColli->UpdateW(64);

    srcRect.x = PosEnemy.x - Camera.x;
    srcRect.y = PosEnemy.y - Camera.y;
    srcRect.w = ENE_WIDTH;
    srcRect.h = ENE_HEIGHT;
}

void Enemy1::Move(Vector2D Target, Collision temp)
{
    VelEnemy.x = 0;
    VelEnemy.y = 0;

    Target.y += 32;
    Target.x += 32;
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
        temp.UpdateH(19 * 2);
        temp.UpdateW(12 * 2);
        temp.UpdateX(Target.x - 32 + 25 * 2);
        temp.UpdateY(Target.y - 32 + 29 * 2);
        if(EnemyColli->checkCollision(temp) == true)
        {
            attack_enemy = true;
            LoadSpriteState(cnt_IDLE_1, IDLE_1, Ene_IDLE_1);
        }
        else
        {
            attack_enemy = false;
            CheckEne_1 = SDL_FLIP_NONE;
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
        }
        else
        {
            VelEnemy.x = 0;
        }

        if(Target.y != PosEnemy.y)
        {
            if(Target.y > PosEnemy.y)
        {
            VelEnemy.y += ENE_VEL;
        }
            else if(Target.y < PosEnemy.y)
        {
            VelEnemy.y -= ENE_VEL;
        }
        }
        else
            {
                VelEnemy.y = 0;
            }

            LoadSpriteState(cnt_MoveAndAttack_1, MoveAndAttack_1, Ene_MoveAndAttack_1);
        }
    }
    }
    else
    {
        if(HealthEnemy <= 0)
            {LoadSpriteState(cnt_Dead_1, Dead_1, Ene_Dead_1);
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

    delete EnemyColli;
    delete EnemyTexture;
}


Enemy2::Enemy2(int x, int y)
{
    PosEnemy.x = x;
    PosEnemy.y = y;

    EnemyColli->UpdateX(PosEnemy.x);
    EnemyColli->UpdateY(PosEnemy.y);
    EnemyColli->UpdateH(34);
    EnemyColli->UpdateW(39);

    EnemyTexture = TextureManager::LoadTexture("latest-ezgif.com-gif-to-sprite-converter.png");

    for(int i = 0; i < Ene_Total_1; i++)
    {
        int tmp = 0;
        switch (i)
        {
        case 0:
            tmp = Move_1;
            break;
        case 1:
            tmp = Attack_1;
            break;
        case 2:
            tmp = Dead_1;
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

Enemy2::~Enemy2()
{
    SDL_DestroyTexture(EnemyTexture);
    delete EnemyTexture;
}

void Enemy2::LoadSpriteState(int &cntState, const int& State, const int& STATE)
{
    int temp = 0;
    temp = cntState;
    cnt_Move_1 = 0;
    cnt_Attack_1 = 0;
    cnt_Dead_1 = 0;
    cntState = temp;
    cntState++;
    if(cntState >= State) cntState = 0;
    Current_Ene_1 = Sprite_1[STATE][cntState];
}

void Enemy2::Move(Vector2D Target, Collision temp, int x, int y)
{

    VelEnemy.x = 0;
    VelEnemy.y = 0;

   // std::cout << x << ';' << y << '\t' << PosEnemy.x << ';' << PosEnemy.y << '\n';
    //Collision *tempCollision = new Collision(0, 0, 64, 64);
//    tempCollision->UpdateX();
//    tempCollision->UpdateY();
//    tempCollision->UpdateW();
//    tempCollision->UpdateH();

    if(HealthEnemy > 0)
    {
        temp.UpdateH(26);
        temp.UpdateW(38);
        temp.UpdateX(x + 26 * 2);
        temp.UpdateY(y + 28 * 2);

        if(EnemyColli->checkCollision(temp) == true || attack_ == true)
        {
            attack_enemy = false;
            attack_ = true;
            LoadSpriteState(cnt_Attack_1, Attack_1, Ene_Attack_1);
            if(cnt_Attack_1 == 0)
            {
                attack_enemy = false;
                attack_ = false;
            }
            else
            {
                if(cnt_Attack_1 == 18 || cnt_Attack_1 == 30)
                {
                    attack_enemy = true;
                }
            }
        }
        else
        {
            attack_enemy = false;
            attack_ = false;
            if(x + 32 > PosEnemy.x )
        {
            CheckEne_1 = SDL_FLIP_NONE;
            VelEnemy.x += ENE_VEL;
        }
        else if(x + 32 < PosEnemy.x)
        {
            CheckEne_1 = SDL_FLIP_HORIZONTAL;
            VelEnemy.x -= ENE_VEL;
        }
        else
        {
        VelEnemy.x = 0;
        CheckEne_1 = SDL_FLIP_NONE;
        }

            if(y + 32 > PosEnemy.y )
        {
            VelEnemy.y += ENE_VEL;
        }
            else if(y + 32 < PosEnemy.y)
        {
            VelEnemy.y -= ENE_VEL;
        }
            else
            {
                VelEnemy.y = 0;            }

            LoadSpriteState(cnt_Move_1, Move_1, Ene_Move_1);
        }
    }
    else
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

void Enemy2::Update(Vector2D Target, Collision temp, SDL_Rect Camera)
{
    Move(Target, temp, Target.x, Target.y);

    PosEnemy.x += VelEnemy.x;
    PosEnemy.y += VelEnemy.y;

    EnemyColli->UpdateX(PosEnemy.x + 20);
    EnemyColli->UpdateY(PosEnemy.y + 7);
    EnemyColli->UpdateH(34);
    EnemyColli->UpdateW(39);



    srcRect.x = PosEnemy.x - Camera.x;
    srcRect.y = PosEnemy.y - Camera.y;
    srcRect.w = ENE_WIDTH;
    srcRect.h = ENE_HEIGHT;
}

void Enemy2::Render()
{
    SDL_RenderCopyEx(Game::Renderer, EnemyTexture, &Current_Ene_1, &srcRect, 0, NULL, CheckEne_1);
}

void Enemy2::Destroy()
{
    SDL_DestroyTexture(EnemyTexture);

    delete EnemyColli;
    delete EnemyTexture;
}

