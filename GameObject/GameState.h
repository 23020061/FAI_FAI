#pragma once
#include "Game.h"
#include <string>
class GameState
{
public:

    virtual void Handle(SDL_Event& e) = 0;
    virtual void Update(int &CurrentState, int &checkChange, std::string &Score, std::string &Name_, int &HighScore, bool &changeMain) = 0;
    virtual void Render() = 0;

    virtual bool Start() = 0;
    virtual bool End() = 0;
    virtual std::string getState() const = 0;

};
