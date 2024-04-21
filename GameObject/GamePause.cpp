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

    if(MenuStop->GetReplay())
    {
        End();
        CurrentState = StartG;
        checkChange = 1;
    }
    else if(MenuStop->GetResume())
    {
        End();
        CurrentState = In;
        checkChange = 1;
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
