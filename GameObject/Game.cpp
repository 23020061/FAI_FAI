#include "Game.h"
#include "bits/stdc++.h"
#include "TextureManager.h"
#include "Character.h"
#include "GameState.h"
#include "StateMachine.h"
#include "GameStart.h"
#include "Ingame.h"
#include "Menu.h"

SDL_Renderer* Game::Renderer = nullptr;

Character* Player;
Uint8 CurrentState = Start;
StateMachine* CurrentMachine = nullptr;
Menu* menu;

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

    SDL_SetRenderDrawColor(Renderer, 125, 200, 100, 255);

    IsRunning = true;

    CurrentMachine = new StateMachine();
    CurrentMachine->Change(new GameStart());
    CurrentState = Start;
    menu = new Menu();
    menu->Init();

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
    }
    switch(CurrentState)
    {
        case Start:
        menu->handle(Event);
        break;
        case In:
        Player->InputHandle(Event);
        break;
        case End:
        break;
    }




}

void Game::Update()
{
    CurrentMachine->Update();
    if(menu->Exit() == true)
        {
            CurrentMachine->Change(new Ingame());
            CurrentState = In;
        }
    switch(CurrentState)
    {
        case Start:
        menu->Update();
        break;
        case In:
        Player->Update();
        break;
        case End:
        break;
    }


}

void Game::Render()
{
    SDL_RenderClear(Renderer);

    CurrentMachine->Render();
    switch(CurrentState)
    {
        case Start:
        menu->Render();
        break;
        case In:
        Player->Render();
        break;
        case End:
        break;
    }

    SDL_RenderPresent(Renderer);
}

void Game::Clean()
{
    SDL_DestroyWindow(Window);

    SDL_DestroyRenderer(Renderer);

    SDL_Quit();
}
