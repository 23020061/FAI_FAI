#include "Menu.h"
#include "StateMachine.h"
#include "Ingame.h"
#include "TextureManager.h"



void Menu::Init()
{
    Table = TextureManager::LoadTexture("Table.png");
    Play = new Button("Play", 640 - 150 / 2, 420 - 60 / 2, 150, 60);
    Quit = new Button("Quit", 640 - 150 / 2, 420 - 60 / 2 + 70, 150, 60);

    Background = TextureManager::LoadTexture("5.png");
    TTF_Init();
    TTF_Font* NameFont;
    FAI_FAI = TextureManager::LoadText("Robus-BWqOd.otf", "FAI_FAI", 200, NameFont, textRect);
}

void Menu::Clear()
{
    //delete Play;
    //delete Quit;

    SDL_DestroyTexture(Table);
    delete Table;

    SDL_DestroyTexture(Background);
    delete Background;

    SDL_DestroyTexture(FAI_FAI);
    delete FAI_FAI;

}

void Menu::Update()
{
    Play->Update();

    Quit->Update();

    if(Play->Enter() == true)
    {
        checkPlay = true;
    }
    if(Quit->Enter() == true)
    {
        checkQuit = true;
    }

    textRect.x = 300;
    textRect.y = 69;
}

void Menu::handle(SDL_Event &e)
{
    Play->handleEvent(e);
    Quit->handleEvent(e);
}

void Menu::Render()
{
    SDL_RenderCopyEx(Game::Renderer, Background, NULL, NULL, 0, NULL, SDL_FLIP_NONE);

    TextureManager::Render(640 - 400 / 2 , 350, 400, 400, Table, NULL, 0, NULL, SDL_FLIP_NONE);

    TextureManager::Render(textRect.x, textRect.y, textRect.w, textRect.h, FAI_FAI, NULL, 0, NULL, SDL_FLIP_NONE);

    Play->Render();
    Quit->Render();

}
