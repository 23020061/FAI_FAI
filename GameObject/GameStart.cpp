#include "GameStart.h"
#include "Menu.h"
#include "Game.h"
const std::string GameStart::StartGame = "GameStart";

Menu* menu;

bool GameStart::End()
{
    menu->Clear();
    delete menu;
    return true;
}

bool GameStart::Start()
{
    menu = new Menu();
    menu->Init();
    return true;
}

void GameStart::Render()
{
        menu->Render();
}

void GameStart::Update(int &CurrentState, int &checkChange)
{
        menu->Update();
        if(menu->InputPlay() == true)
        {
            End();
            CurrentState = In;
            checkChange = 1;
        }
        else if(menu->InputQuit() == true)
        {
            End();
            CurrentState = Quit;
            checkChange = 1;
        }
}

void GameStart::Handle(SDL_Event& e)
{
    menu->handle(e);
}
