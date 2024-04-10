#include "Menu.h"
#include "StateMachine.h"
#include "Ingame.h"
#include "TextureManager.h"
void Menu::Init()
{
    Play = new Button("play.png", 640 - 130, 500 - 95 / 2, 260, 95);
    Background = TextureManager::LoadTexture("5.png");
    TTF_Init();
    TTF_Font* NameFont;
    FAI_FAI = TextureManager::LoadText("monogram.ttf", "FAI_FAI", 500, NameFont);
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

    TextureManager::Render(500, 200, 400, 400, FAI_FAI, NULL, 0, NULL, SDL_FLIP_NONE);

    Play->Render();

}
