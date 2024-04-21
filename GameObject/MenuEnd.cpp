#include "MenuEnd.h"
#include "StateMachine.h"
#include "TextureManager.h"
void MenuEnd::Init()
{
    Table = TextureManager::LoadTexture("Table.png");
    Replay = new Button("Replay", 640 - 150 / 2, 420 - 60 / 2, 150, 60);
    Quit = new Button("Quit", 640 - 150 / 2, 420 - 60 / 2 + 70, 150, 60);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    MusicEnd = Mix_LoadMUS("13-Flap.mp3");
    Mix_PlayMusic(MusicEnd, -1);

    Background = TextureManager::LoadTexture("5.png");
    TTF_Init();
    TTF_Font* NameFont;
    GameOver = TextureManager::LoadText("Robus-BWqOd.otf", "Game Over!", 200, NameFont, textRect);
}

void MenuEnd::Update(std::string &Score)
{
    Replay->Update();
    Quit->Update();
    TTF_Font* ScoreFont;
    std::string temp = "Your " + Score;
    ScoreTex = TextureManager::LoadText("monogram.ttf", temp.c_str(), 100, ScoreFont, ScoreRect);

    if(Replay->Enter() == true)
    {
        checkReplay = true;
    }
    if(Quit->Enter() == true)
    {
        checkQuit = true;
    }

    textRect.x = 300;
    textRect.y = 69;
}

void MenuEnd::handle(SDL_Event &e)
{
    Replay->handleEvent(e);
    Quit->handleEvent(e);
}

void MenuEnd::Render()
{
    SDL_RenderCopyEx(Game::Renderer, Background, NULL, NULL, 0, NULL, SDL_FLIP_NONE);

    TextureManager::Render(640 - 400 / 2 , 350, 400, 400, Table, NULL, 0, NULL, SDL_FLIP_NONE);

    TextureManager::Render(textRect.x, textRect.y, textRect.w, textRect.h, GameOver, NULL, 0, NULL, SDL_FLIP_NONE);
    TextureManager::Render(640 - 400 / 2 - 10 , 250, ScoreRect.w, ScoreRect.h, ScoreTex, NULL, 0, NULL, SDL_FLIP_NONE);
    Replay->Render();
    Quit->Render();

}

void MenuEnd::Clear()
{
    SDL_DestroyTexture(Background);
    SDL_DestroyTexture(Table);
    SDL_DestroyTexture(GameOver);
    Mix_FreeMusic(MusicEnd);
    MusicEnd = NULL;
    Mix_Quit();

    delete Background, Table, GameOver;
    delete Replay;
    delete Quit;

}

