
#include "MenuPause.h"
#include "TextureManager.h"
void MenuPause::Init()
{
    TablePause = TextureManager::LoadTexture("Table.png");
    Resume = new Button("Resume", 640 - 150 / 2, 420 - 60 / 2, 150, 60);
    Regame = new Button("Replay", 640 - 150 / 2, 420 - 60 / 2 + 70, 150, 60);

}
void MenuPause::Clear()
{
    delete Resume;
    delete Regame;
    SDL_DestroyTexture(TablePause);
    delete TablePause;

}

void MenuPause::Update()
{
    Resume->Update();

    Regame->Update();

    if(Resume->Enter())
    {
        checkResume = true;
    }
    else if(Regame->Enter())
    {
        checkRegame = true;
    }
}

void MenuPause::handle(SDL_Event &e)
{
    Resume->handleEvent(e);
    Regame->handleEvent(e);

}

void MenuPause::Render()
{
    TextureManager::Render(640 - 400 / 2 , 350, 400, 400, TablePause, NULL, 0, NULL, SDL_FLIP_NONE);

    Resume->Render();
    Regame->Render();

}
