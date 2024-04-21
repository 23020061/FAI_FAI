#pragma once


#include "Game.h"
#include "Button.h"
#include <SDL_mixer.h>

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

    Mix_Music* MusicStart = NULL;

    bool checkPlay, checkQuit;
};
