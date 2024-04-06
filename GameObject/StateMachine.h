#pragma once


#include "GameState.h"
#include <vector>

class StateMachine
{
public:

    void Push(GameState* TempState);
    void Change(GameState* TempState);
    void Popback();

    void Render();
    void Update();
private:

    std::vector<GameState*> Machine;

};
