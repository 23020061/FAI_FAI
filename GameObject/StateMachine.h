#pragma once


#include "GameState.h"
#include <vector>

class StateMachine
{
public:

    void Push(GameState* TempState);

    void Change(GameState* TempState);

    void Popback();

    void Handle(SDL_Event &e);

    void Render();

    void Update(int &CurrentState, int &checkChange, std::string &Score);

    std::vector<GameState*> Machine;

private:



};
