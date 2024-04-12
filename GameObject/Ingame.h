#pragma once

#include "Game.h"
#include "GameState.h"

class Ingame : public GameState
{
public:

    virtual bool Start();
    virtual bool End();

    virtual void Handle(SDL_Event& e);
    virtual void Update(int &CurrentState, int &checkChange);
    virtual void Render();
    virtual std::string getState() const
    {
        return GameIn;
    }
private:
    static const std::string GameIn;

};
