#pragma once
#include "Game.h"
#include <string>
class GameState
{
public:

    virtual void Update() = 0;
    virtual void Render() = 0;

    virtual bool Start() = 0;
    virtual bool End() = 0;
    virtual std::string getState() const = 0;

};
