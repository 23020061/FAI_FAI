
#include "MenuPause.h"
#include "TextureManager.h"
void MenuPause::Init()
{
    Resume = new Button("Resume", 640 - 150 / 2, 420 - 60 / 2, 150, 60);
    Regame = new Button("Replay", 640 - 150 / 2, 420 - 60 / 2 + 70, 150, 60);

}
void MenuPause::Clear()
{
    delete Resume;
    delete Regame;


}

void MenuPause::Update()
{
    Resume->Update();

    Regame->Update();

    if( Resume->Enter() == true )
    {
        checkResume = true;
    }
    else if( Regame->Enter() == true)
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
    Resume->Render();
    Regame->Render();

}
