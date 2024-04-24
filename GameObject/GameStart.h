#pragma once

#include "Game.h"
#include "GameState.h"
#include "SDL_ttf.h"

class GameStart : public GameState
{
public:
    virtual bool Start();
    virtual bool End();
    virtual void Handle(SDL_Event& e);

    virtual void Update(int &CurrentState, int &checkChange, std::string &Score, std::string &Name_, int &HighScore, bool &changeMain);
    virtual void Render();

    virtual std::string getState() const
    {
        return StartGame;
    }

    std::string TextName = "Your Name:";
    SDL_Texture* TexName;
    TTF_Font* TTFTextName = NULL;
    SDL_Rect RectTextName;

    std::string SaveName = " ";
    SDL_Texture* YourName;
    TTF_Font* Name;
    SDL_Rect RectName;
    bool checkName = false;

private:

    static const std::string StartGame;

};
