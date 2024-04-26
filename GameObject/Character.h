#pragma once

#include "Game.h"
#include "Vector2D.h"
#include "Collision.h"
#include "bits/stdc++.h"
#include "Enemy.h"
#include <SDL_ttf.h>

enum
{
    STATE_IDLE = 0,
    STATE_MOVERUN = 1,
    STATE_JUMP = 2,
    STATE_FALL = 3,
    STATE_GROUNDIMPACT = 4,
    STATE_ATTACK = 5,
    STATE_TAKINGDAMAGE = 6,
    STATE_DEAD = 7,
    STATE_SHIELDBLOCKING = 8,
    STATE_TOTAL = 9
};

const int MAP_WIDTH = 3200;
const int MAP_HEIGHT = 3200;
const int CAM_WIDTH = 1280;
const int CAM_HEIGHT = 800;


class Character
{
public:
    Character(const char* path, int x, int y);

    ~Character();

    void Fresh();

    const Uint8* CurrentKeyState = SDL_GetKeyboardState(NULL);

    void InputHandle(SDL_Event &event);

    void LoadSpriteState(int& cntState, const int& State, const int& STATE);

    void Move(const std::vector <Collision> &MapColli);

    void Camera();

    void Update(std::vector <Collision> MapColli, std::vector<Enemy1*> &Enemy, std::vector<Enemy2*> &EnemyOther);

    void Render();

    SDL_Rect GetPositionCam()
    {
        return Cam;
    }

    Vector2D getPosChar()
    {
        return Position;
    }

    bool Exit()
    {
        return check;
    }

    bool EnterP()
    {
    return checkP;
    }

    std::string getScore()
    {
        return total;
    }

    Collision GetColli();
private:

    SDL_Texture* TimeCoolDownAttack;
    SDL_Rect TimeAttack;
    SDL_Texture* ButtonAttack;


    Vector2D Position;
    Vector2D Velocity;
    SDL_Texture* CharTex;
    SDL_Rect srcRect;
    SDL_Rect Cam;
    bool check = false;
    bool CoolDownAttack = false;
    Uint32 CurrentTime = SDL_GetTicks();


    SDL_Texture *HealthLeft, *HealthHolderLeft;
    SDL_Texture *HealthRight, *HealthHolderRight;
    SDL_Texture *HealthCenter, *HealthHolderCenter;
    SDL_Texture *IconHealth;

    SDL_Texture *ExpLeft, *ExpHolderLeft;
    SDL_Texture *ExpRight, *ExpHolderRight;
    SDL_Texture *ExpCenter, *ExpHolderCenter;
    SDL_Texture *IconExp;

    float Health_Char = 100;
    int checkAttack = 0;
    int checkAttackOther = 0;
    int checkDead = 0;
    int Exp_Char = 0;
    int cntPath = 1;

    int Score = 0;
    int Armor = 1;
    SDL_Texture* TexScore;
    TTF_Font* ScoreFont = NULL;
    SDL_Rect RectScore;
    std::string ScoreChar = "Score:";
    std::string total = "";
    bool checkP = false;
};

