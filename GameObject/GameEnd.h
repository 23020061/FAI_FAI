#pragma once

#include "GameState.h"
#include "MenuEnd.h"
class GameEnd : public GameState
{
public:

    virtual bool Start();
    virtual bool End();
    virtual void Update();
    virtual void Render();
    virtual std::string getState() const
    {
        return EndGame;
    }
private:
    static const std::string EndGame;

};
