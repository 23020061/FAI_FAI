#pragma once

#include "GameState.h"
#include "MenuEnd.h"
class GameEnd : public GameState
{
public:

    virtual bool Start();
    virtual bool End();
    virtual void Update(int &CurrentState, int &checkChange);
    virtual void Render();
    virtual void Handle(SDL_Event &Event);

    virtual std::string getState() const
    {
        return EndGame;
    }
private:
    static const std::string EndGame;

};
