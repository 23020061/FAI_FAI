#pragma once
#include "Game.h"
#include <string>
class GameState
{
public:

    virtual void Handle(SDL_Event& e) = 0;
    virtual void Update(int &CurrentState, int &checkChange, std::string &Score) = 0;
    virtual void Render() = 0;

    virtual bool Start() = 0;
    virtual bool End() = 0;
    virtual std::string getState() const = 0;

};
