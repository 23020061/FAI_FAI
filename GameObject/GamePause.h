#pragma once

#include "GameState.h"
#include "MenuPause.h"

class GamePause : public GameState
{
public:

    virtual bool Start();
    virtual bool End();
    virtual void Update(int &CurrentState, int &checkChange, std::string &Score, std::string &Name_, int &HighScore, bool &changeMain);
    virtual void Render();
    virtual void Handle(SDL_Event &Event);

    virtual std::string getState() const
    {
        return PauseGame;
    }
private:
    static const std::string PauseGame;

};
