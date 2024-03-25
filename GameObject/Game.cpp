#include "Game.h"
#include "bits/stdc++.h"
#include "TextureManager.h"
#include "Character.h"

SDL_Renderer* Game::Renderer = nullptr;
enum GameState
{
    GameStart,
    Ingame,
    GameEnd

};


Character* Player;

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char* title, int x, int y, int Width, int Height, bool FullScreen)
{
    int flags = 0;
    if(FullScreen == true)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    SDL_Init(SDL_INIT_EVERYTHING);

    Window = SDL_CreateWindow(title, x, y, Width, Height, flags);

    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_SetRenderDrawColor(Renderer, 255, 255, 0, 255);

    IsRunning = true;

    Player = new Character("16x16 knight 3.png", 128, 128);

}

void Game::HandleEvents()
{
    SDL_Event Event;

    SDL_PollEvent( &Event );

    switch(Event.type)
    {
        case SDL_QUIT:
            IsRunning = false;
            break;
        default:
            Player->InputHandle(Event);
            break;
    }
}

void Game::Update()
{
    Player->Update();
}

void Game::Render()
{
    SDL_RenderClear(Renderer);

    Player->Render();

    SDL_RenderPresent(Renderer);
}

void Game::Clean()
{
    SDL_DestroyWindow(Window);

    SDL_DestroyRenderer(Renderer);

    SDL_Quit();
}
