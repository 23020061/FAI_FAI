#pragma once

#include "Game.h"
#include "Vector2D.h"
#include "Collision.h"
#include "bits/stdc++.h"
#include "Enemy.h"

enum
{
    STATE_IDLE,
    STATE_MOVERUN,
    STATE_JUMP,
    STATE_FALL,
    STATE_GROUNDIMPACT,
    STATE_ATTACK,
    STATE_TAKINGDAMAGE,
    STATE_DEAD,
    STATE_SHIELDBLOCKING,
    STATE_TOTAL
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

    void Move(std::vector <Collision> MapColli);

    void Camera();

    void Update(std::vector <Collision> MapColli, std::vector<Enemy1*> Enemy);

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

    int Health_Char = 100;

private:

    Vector2D Position;
    Vector2D Velocity;
    SDL_Texture* CharTex;
    SDL_Rect srcRect;
    SDL_Rect Cam;
    bool check = false;

    SDL_Texture *HealthLeft, *HealthHolderLeft;
    SDL_Texture *HealthRight, *HealthHolderRight;
    SDL_Texture *HealthCenter, *HealthHolderCenter;
    SDL_Texture *IconHealth;

    SDL_Texture *ExpLeft, *ExpHolderLeft;
    SDL_Texture *ExpRight, *ExpHolderRight;
    SDL_Texture *ExpCenter, *ExpHolderCenter;
    SDL_Texture *IconExp;

    int Exp_Char = 0;
    int cntPath = 1;
};

