#include "Character.h"
#include "TextureManager.h"
#include "Map.h"
#include "Collision.h"

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

const float CHARACTER_VEL = 10;

const int CHAR_WIDTH = 64;
const int CHAR_HEIGHT = 64;

Collision ColliChar(1600 + 54, 1600 + 58, 12 * 2, 19 * 2);

Character::Character(const char* path, int x, int y)
{
    CharTex = TextureManager::LoadTexture(path);

    Position.x = x;
    Position.y = y;

    Cam.w = CAM_WIDTH;
    Cam.h = CAM_HEIGHT;

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
            Sprite[i][j].x = CHAR_WIDTH * j;
            Sprite[i][j].y = CHAR_HEIGHT * i;
            Sprite[i][j].w = CHAR_WIDTH;
            Sprite[i][j].h = CHAR_HEIGHT;
        }
    }
}

void Character::Move(std::vector<Collision> MapColli)
{
    Position.x += Velocity.x;
    ColliChar.UpdateX(Position.x + 54);
    bool checkCharX = false;

    for(int i = 0; i < MapColli.size(); i++)
    {
       if(ColliChar.checkCollision(MapColli[i]) == true && checkCharX == false)
        {
            checkCharX = true;
            //std::cout << '(' << MapColli[i].getCollisionBox().x << ';'<< MapColli[i].getCollisionBox().y << ')' << '\n';
            //std::cout << Position.x << ' ' << Position.y << '\n';
            break;
        }
    }

    if((Position.x < 0) || (Position.x > MAP_WIDTH - CHAR_WIDTH * 2) || checkCharX == true)
    {
        Position.x -= Velocity.x;
    }

    Position.y += Velocity.y;

    ColliChar.UpdateY(Position.y + 58);

    bool checkCharY = false;

    for(int i = 0; i < MapColli.size(); i++)
    {
    if(ColliChar.checkCollision(MapColli[i]))
        {
            checkCharY = true;
            //break;
        }
    }
    if((Position.y < 0) || (Position.y > MAP_HEIGHT - CHAR_HEIGHT * 2) || checkCharY == true)
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

        SDL_PumpEvents();

        if(CurrentKeyState[SDL_SCANCODE_J])
        {
            LoadSpriteState(cntATTACK, ATTACK, STATE_ATTACK);
        }
        else if(CurrentKeyState[SDL_SCANCODE_K])
        {
            LoadSpriteState(cntSHEILDBLOCKING, SHIELDBLOCKING, STATE_SHIELDBLOCKING);
        }
        else
        {
            //if()
            bool state = false;
            if(CurrentKeyState[SDL_SCANCODE_D])
        {
            state = true;
            Check = SDL_FLIP_NONE;
            LoadSpriteState(cntMOVERUN, MOVERUN, STATE_MOVERUN);
            Velocity.x += CHARACTER_VEL;
        }
        if(CurrentKeyState[SDL_SCANCODE_A])
        {
            state = true;
            Check = SDL_FLIP_HORIZONTAL;
            LoadSpriteState(cntMOVERUN, MOVERUN, STATE_MOVERUN);
            Velocity.x -= CHARACTER_VEL;
        }
        if(CurrentKeyState[SDL_SCANCODE_S])
        {
            state = true;
            LoadSpriteState(cntMOVERUN, MOVERUN, STATE_MOVERUN);
            Velocity.y += CHARACTER_VEL;
        }
        if(CurrentKeyState[SDL_SCANCODE_W])
        {
            state = true;
            LoadSpriteState(cntMOVERUN, MOVERUN, STATE_MOVERUN);
            Velocity.y -= CHARACTER_VEL;
        }

        if(state == false)
        {
            LoadSpriteState(cntIDLE, IDLE, STATE_IDLE);
        }

        }
}

void Character::Camera()
{
    Cam.x = (Position.x + CHAR_WIDTH / 2) - CAM_WIDTH / 2;
    Cam.y = (Position.y + CHAR_HEIGHT / 2) - CAM_HEIGHT / 2;

    if(Cam.x < 0)
    {
        Cam.x = 0;
    }
    if(Cam.y < 0)
    {
        Cam.y = 0;
    }

    if(Cam.x > MAP_WIDTH - CAM_WIDTH)
    {
        Cam.x = MAP_WIDTH - CAM_WIDTH;
    }

    if(Cam.y > MAP_HEIGHT - CAM_HEIGHT)
    {
        Cam.y = MAP_HEIGHT - CAM_HEIGHT;
    }
}

void Character::Update(std::vector <Collision> MapColli)
{
    Move(MapColli);

    Camera();

    srcRect.x  = Position.x - Cam.x;
    srcRect.y  = Position.y - Cam.y;

    srcRect.w = CHAR_WIDTH * 2;
    srcRect.h = CHAR_HEIGHT * 2;

}

void Character::Render()
{
    //SDL_RenderCopyEx(Game::Renderer, MapTex, &Cam, NULL, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(Game::Renderer, CharTex, &Current, &srcRect, 0, NULL, Check);
}
