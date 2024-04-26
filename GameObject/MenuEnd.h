#pragma once
#include "Game.h"
#include "Button.h"
#include <SDL_mixer.h>

class MenuEnd
{
public:
    void handle(SDL_Event &e);

    void Update(std::string &Score);

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

    Mix_Music* MusicEnd = NULL;

    SDL_Texture* ScoreTex;
    SDL_Rect ScoreRect;


    bool checkReplay, checkQuit;
};
