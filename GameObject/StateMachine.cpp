#include "StateMachine.h"

void StateMachine::Push(GameState* TempState)
{
    Machine.push_back(TempState);
    Machine.back()->Start();
}

void StateMachine::Popback()
{
    if(Machine.empty() == false)
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
                {delete Machine.back();
                Machine.pop_back();
                }
        }
    }
    Machine.push_back(TempState);
    Machine.back()->Start();

}

void StateMachine::Render()
{
    Machine.back()->Render();
}

void StateMachine::Update()
{
    Machine.back()->Update();
}