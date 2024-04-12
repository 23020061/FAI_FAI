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

    bool InputPlay()
    {
        return checkPlay;
    }

    bool InputQuit()
    {
        return checkQuit;
    }

private:
    SDL_Texture* Background;

    Button* Play;
    Button* Quit;

    SDL_Texture* Table;
    SDL_Texture* FAI_FAI;
    SDL_Rect textRect;


    bool checkPlay, checkQuit;
};
