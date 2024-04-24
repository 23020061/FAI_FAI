#include "GameStart.h"
#include "Menu.h"
#include "Game.h"
#include "TextureManager.h"

const std::string GameStart::StartGame = "GameStart";

Menu* menu;

bool GameStart::End()
{
    SDL_DestroyTexture(YourName);
    delete YourName;

    SDL_DestroyTexture(TexName);
    delete TexName;
    menu->Clear();
    delete menu;

    delete Name;

    SDL_StopTextInput();
    return true;
}

bool GameStart::Start()
{
    TTF_Init();
    SDL_StartTextInput();
    SaveName = " ";
    menu = new Menu();
    menu->Init();
    TexName = TextureManager::LoadText("monogram.ttf", TextName.c_str(), 50, TTFTextName, RectTextName);

    return true;
}

void GameStart::Render()
{
        menu->Render();
        if(SaveName.length() > 1)
        {
            TextureManager::Render(580, 100, RectName.w, RectName.h, YourName, NULL, 0, NULL, SDL_FLIP_NONE);
        }
        TextureManager::Render(400, 100, RectTextName.w, RectTextName.h, TexName, NULL, 0, NULL, SDL_FLIP_NONE);
}

void GameStart::Update(int &CurrentState, int &checkChange, std::string &Score, std::string &Name_, int &HighScore, bool &changeMain)
{
        YourName = TextureManager::LoadText("monogram.ttf", SaveName.c_str(), 50, Name, RectName);
        menu->Update();
        checkChange = 0;
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
        Name_ = SaveName;
}

void GameStart::Handle(SDL_Event& e)
{
    if(e.type == SDL_KEYDOWN)
    {
        if(e.key.keysym.sym == SDLK_BACKSPACE && SaveName.length() > 1)
    {
        SaveName.pop_back();
    }
    }
    else if(SaveName.length() <= 20)
    {
        if(e.type == SDL_TEXTINPUT)
        {
            SaveName += e.text.text;
        }
    }

    menu->handle(e);
}
