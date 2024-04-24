#include "Menu.h"
#include "StateMachine.h"
#include "Ingame.h"
#include "TextureManager.h"
#include <SDL_mixer.h>


void Menu::Init()
{

    Table = TextureManager::LoadTexture("Table.png");
    Play = new Button("Play", 640 - 150 / 2, 420 - 60 / 2, 150, 60);
    Quit = new Button("Quit", 640 - 150 / 2, 420 - 60 / 2 + 70, 150, 60);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    MusicStart = Mix_LoadMUS("21-Raid2.mp3");

    Background = TextureManager::LoadTexture("5.png");
    TTF_Init();
    TTF_Font* NameFont;
    FAI_FAI = TextureManager::LoadText("Robus-BWqOd.otf", "FAI_FAI", 200, NameFont, textRect);
    Mix_PlayMusic(MusicStart, -1);
}

void Menu::Clear()
{
    Mix_FreeMusic(MusicStart);
    MusicStart = NULL;
    delete Play;
    delete Quit;

    SDL_DestroyTexture(Table);
    delete Table;

    SDL_DestroyTexture(Background);
     Background = NULL;

    SDL_DestroyTexture(FAI_FAI);
    delete FAI_FAI;
    Mix_Quit();

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
