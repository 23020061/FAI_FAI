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

    void Render(int x);

    void Update(int &CurrentState, int &checkChange, std::string &Score, std::string &Name_, int &HighScore, bool &changeMain);

private:

    std::vector<GameState*> Machine;


};
