
#pragma once
#include "Button.h"

class MenuPause
{
public:

    void handle(SDL_Event &e);

    void Update();

    void Render();

    void Init();

    void Clear();

    bool GetReplay()
    {
        return checkRegame;
    }

    bool GetResume()
    {
        return checkResume;
    }

private:

    SDL_Texture* TablePause;

    Button* Resume;
    Button* Regame;

    bool checkRegame, checkResume;

};
