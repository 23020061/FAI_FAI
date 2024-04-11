#pragma once
#include "Game.h"
#include "Button.h"


class MenuEnd
{
public:
    void handle(SDL_Event &e);

    void Update();

    void Render();

    void Init();

    void Clear();

    bool InputReplay()
    {
        return checkReplay;
    }

    bool InputQuit()
    {
        return checkQuit;
    }
private:

    SDL_Texture* Background;

    Button* Replay;
    Button* Quit;

    SDL_Texture* Table;
    SDL_Texture* GameOver;

    SDL_Rect textRect;

    bool checkReplay, checkQuit;
};
