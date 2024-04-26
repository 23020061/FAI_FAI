#include "GameEnd.h"
#include "MenuEnd.h"

const std::string GameEnd::EndGame = "GameEnd";
MenuEnd* MenuExit;
bool GameEnd::Start()
{
    MenuExit = new MenuEnd();
    MenuExit->Init();
    return true;
}

bool GameEnd::End()
{
    MenuExit->Clear();
    delete MenuExit;
    return true;
}

void GameEnd::Update(int &CurrentState, int &checkChange, std::string &Score)
{
        MenuExit->Update(Score);
        if(MenuExit->InputReplay() == true)
        {
            End();
            CurrentState = StartG;
            checkChange = 1;
        }
        if(MenuExit->InputQuit() == true)
        {
            End();
            CurrentState = Quit;
            checkChange = 1;
        }
}

void GameEnd::Render()
{
        MenuExit->Render();
}

void GameEnd::Handle(SDL_Event& Event)
{
        MenuExit->handle(Event);
}
