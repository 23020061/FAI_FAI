#include "Character.h"
#include "TextureManager.h"

int IDLE = 5, cntIDLE = 0,
    MOVERUN = 8, cntMOVERUN = 0,
    JUMP = 3, cntJump = 0,
    FALL = 1, cntFALL = 0,
    GROUNDIMPACT = 2, cntGROUNDIMPACT = 0,
    ATTACK = 3, cntATTACK = 0,
    TAKINGDAMAGE = 1, cntTAKINGDAMAGE = 0,
    DEAD = 6, cntDEAD = 0,
    SHIELDBLOCKING = 2, cntSHEILDBLOCKING = 0;

SDL_Rect Sprite[STATE_TOTAL][10];
SDL_Rect Current;
SDL_RendererFlip Check = SDL_FLIP_NONE;

const float CHARACTER_VEL = 4;


Character::Character(const char* path, int x, int y)
{
    CharTex = TextureManager::LoadTexture(path);

    for(int i = 0; i < STATE_TOTAL; i++)
    {
        int tmp;
        switch(i)
        {
        case 0:
            tmp = IDLE;
            break;
        case 1:
            tmp = MOVERUN;
            break;
        case 2:
            tmp = JUMP;
            break;
        case 3:
            tmp = FALL;
            break;
        case 4:
            tmp = GROUNDIMPACT;
            break;
        case 5:
            tmp = ATTACK;
            break;
        case 6:
            tmp = TAKINGDAMAGE;
            break;
        case 7:
            tmp = DEAD;
            break;
        case 8:
            tmp = SHIELDBLOCKING;
            break;
        }

        for(int j = 0; j < tmp; j++)
        {
            Sprite[i][j].x = 64 * j;
            Sprite[i][j].y = 64 * i;
            Sprite[i][j].w = 64;
            Sprite[i][j].h = 64;
        }
    }
}

void Character::Move()
{
    Position.x += Velocity.x;

    if((Position.x < 0) || (Position.x + srcRect.w > 1280))
    {
        Position.x -= Velocity.x;
    }

    Position.y += Velocity.y;

    if( ( Position.y < 0 ) || ( Position.y + srcRect.h > 800 ) )
    {
        Position.y -= Velocity.y;
    }

}

void Character::Fresh()
{
    cntIDLE = 0;
    cntMOVERUN = 0;
    cntJump = 0;
    cntFALL = 0;
    cntGROUNDIMPACT = 0;
    cntATTACK = 0;
    cntTAKINGDAMAGE = 0;
    cntDEAD = 0;
    cntSHEILDBLOCKING = 0;
}
void Character::LoadSpriteState(int& cntState, const int& State, const int& STATE)
{
    int temp;
    temp = cntState;
    Fresh();
    cntState = temp;
    cntState++;
    if(cntState >= State) cntState = 0;
    Current = Sprite[STATE][cntState];
}

void Character::InputHandle(SDL_Event& event)
{
        Velocity.x = 0;
        Velocity.y = 0;
        if(CurrentKeyState[SDL_SCANCODE_J])
        {
            LoadSpriteState(cntATTACK, ATTACK, STATE_ATTACK);
        }
        else if(CurrentKeyState[SDL_SCANCODE_D])
        {
            Check = SDL_FLIP_NONE;
            LoadSpriteState(cntMOVERUN, MOVERUN, STATE_MOVERUN);
            Velocity.x += CHARACTER_VEL;
        }
        else if(CurrentKeyState[SDL_SCANCODE_A])
        {
            Check = SDL_FLIP_HORIZONTAL;
            LoadSpriteState(cntMOVERUN, MOVERUN, STATE_MOVERUN);
            Velocity.x -= CHARACTER_VEL;
        }
        else if(CurrentKeyState[SDL_SCANCODE_S])
        {
            LoadSpriteState(cntMOVERUN, MOVERUN, STATE_MOVERUN);
            Velocity.y += CHARACTER_VEL;
        }
        else if(CurrentKeyState[SDL_SCANCODE_W])
        {
            LoadSpriteState(cntMOVERUN, MOVERUN, STATE_MOVERUN);
            Velocity.y -= CHARACTER_VEL;
        }
        else if(CurrentKeyState[SDL_SCANCODE_J])
        {
            LoadSpriteState(cntATTACK, ATTACK, STATE_ATTACK);
        }
        else
        {
            LoadSpriteState(cntIDLE, IDLE, STATE_IDLE);
        }
}

void Character::Update()
{
    Move();

    srcRect.x = Position.x;
    srcRect.y = Position.y;
    srcRect.w = 64 * 1.5;
    srcRect.h = 64 * 1.5;
}

void Character::Render()
{
    SDL_RenderCopyEx(Game::Renderer, CharTex, &Current, &srcRect, 0, NULL, Check);
}
