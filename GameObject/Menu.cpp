#include "Menu.h"
#include "StateMachine.h"
#include "Ingame.h"
#include "TextureManager.h"
void Menu::Init()
{
    Play = new Button("play.png", 200, 200, 260, 95);
    Background = TextureManager::LoadTexture("background.png");
}

void Menu::Update()
{
    Play->Update();

    if(Play->Enter() == true)
    {
        check = true;
    }
}

void Menu::handle(SDL_Event &e)
{
    Play->handleEvent(e);
}

void Menu::Render()
{
    SDL_RenderCopyEx(Game::Renderer, Background, NULL, NULL, 0, NULL, SDL_FLIP_NONE);

    Play->Render();
}
