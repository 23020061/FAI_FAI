#pragma once


#include "Game.h"
#include "Button.h"

class Menu
{
public:
    void handle(SDL_Event &e);

    void Update();

    void Render();

    void Init();

    void Clear();

    bool Exit()
    {
        return check;
    }

private:
    SDL_Texture* Background;

    Button* Play;

    bool check;
};
