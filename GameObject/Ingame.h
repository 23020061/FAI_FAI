#pragma once

#include "Game.h"
#include "GameState.h"
#include "Map.h"
#include "Character.h"
#include <SDL_mixer.h>

class Ingame : public GameState
{
public:

    virtual bool Start();
    virtual bool End();

    virtual void Handle(SDL_Event& e);
    virtual void Update(int &CurrentState, int &checkChange, std::string &Score);
    virtual void Render();
    virtual std::string getState() const
    {
        return GameIn;
    }
private:
    static const std::string GameIn;

    Map* MAP;

    Mix_Music* Music = NULL;

    Character* Player;

    std::vector <Enemy1*> Enemy1_;

    std::vector <Enemy2*> Enemy2_;
};
