#include "Enemy.h"
#include "TextureManager.h"
#include "Game.h"

const int ENE_WIDTH = 64;
const int ENE_HEIGHT = 64;
const int ENE_VEL = 4;

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


void Enemy1::Update(Vector2D Target)
{
    Move(Target);

    PosEnemy.x += VelEnemy.x;
    PosEnemy.y += VelEnemy.y;

    srcRect.x = PosEnemy.x;
    srcRect.y = PosEnemy.y;
    srcRect.w = ENE_WIDTH;
    srcRect.h = ENE_HEIGHT;
}

void Enemy1::Move(Vector2D Target)
{
    VelEnemy.x = 0;
    VelEnemy.y = 0;

    if(Target.x != PosEnemy.x)
    {
        if(Target.x > PosEnemy.x)
    {
        CheckEne_1 = SDL_FLIP_HORIZONTAL;
        //LoadSpriteState(cnt_MoveAndAttack_1, MoveAndAttack_1, Ene_MoveAndAttack_1);
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

void Enemy1::Render()
{
    SDL_RenderCopyEx(Game::Renderer, EnemyTexture, &Current_Ene_1, &srcRect, 0, NULL, CheckEne_1);

}
