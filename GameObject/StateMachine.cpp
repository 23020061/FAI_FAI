#include "StateMachine.h"

void StateMachine::Push(GameState* TempState)
{
    Machine.push_back(TempState);
    Machine.back()->Start();
}

void StateMachine::Popback()
{
    if(!Machine.empty())
    {
        if(Machine.back()->End())
        {
            delete Machine.back();
            Machine.pop_back();
        }
    }
}

void StateMachine::Change(GameState* TempState)
{
    if(Machine.empty() == false)
    {
        if(Machine.back()->getState() == TempState->getState())
        {
            return;
        }
        else
        {
                if(Machine.back()->End())
                {
                delete Machine.back();
                Machine.pop_back();
                }
        }
    }
    Machine.push_back(TempState);
    Machine.back()->Start();

}

void StateMachine::Render(int x)
{
    if(x == 1)
        {
            Machine.back()->Render();
        }
    if(x == 2)
    {
        Machine[Machine.size() - 2]->Render();
        Machine.back()->Render();
    }
}

void StateMachine::Update(int &CurrentState, int &checkChange, std::string &Score, std::string &Name_, int &HighScore, bool &changeMain)
{
    Machine.back()->Update(CurrentState, checkChange, Score, Name_, HighScore, changeMain);
}

void StateMachine::Handle(SDL_Event &e)
{
    Machine.back()->Handle(e);
}
