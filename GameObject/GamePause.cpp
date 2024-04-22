#include "GamePause.h"

const std::string GamePause::PauseGame = "GamePause";

MenuPause* MenuStop;

bool GamePause::Start()
{
    MenuStop = new MenuPause();
    MenuStop->Init();
    return true;
}

bool GamePause::End()
{
    MenuStop->Clear();
    delete MenuStop;
    return true;
}

void GamePause::Update(int &CurrentState, int &checkChange, std::string &Score)
{
    MenuStop->Update();

    if(MenuStop->GetReplay() == true)
    {
        End();
        CurrentState = StartG;
        checkChange = 1;
    }
    else if(MenuStop->GetResume() == true)
    {
        CurrentState = In;
        checkChange = 2;
    }
}

void GamePause::Handle(SDL_Event&e)
{
    MenuStop->handle(e);
}

void GamePause::Render()
{
    MenuStop->Render();
}
