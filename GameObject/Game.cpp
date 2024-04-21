#include "Game.h"
#include "bits/stdc++.h"
#include "TextureManager.h"
#include "Character.h"
#include "GameState.h"
#include "StateMachine.h"
#include "GameStart.h"
#include "Ingame.h"
#include "Menu.h"
#include "Map.h"
#include "Collision.h"
#include "Enemy.h"
#include "GameEnd.h"
#include "MenuEnd.h"
#include "GamePause.h"


SDL_Renderer* Game::Renderer = nullptr;
int CurrentState = StartG;
StateMachine* Machine;
int checkChange = 0;
Game::Game(){}
Game::~Game(){}
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

    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);

    IsRunning = true;

    Machine = new StateMachine();

    Machine->Push( new GameStart());

    CurrentState = StartG;
}
void Game::HandleEvents()
{
    SDL_Event Event;
    SDL_PollEvent( &Event );

    switch(Event.type)
    {
        case SDL_QUIT:
            IsRunning = false;
            SDL_DestroyWindow(Window);
            break;
    }
    Machine->Handle(Event);
}
void Game::Update()
{
    checkChange = 0;
    Machine->Update(CurrentState, checkChange);

    if(checkChange != 0)
    {
        switch(CurrentState)
         {
    case StartG:
        Machine->Change(new GameStart());
        break;
    case In:
        Machine->Change(new Ingame());
        break;
    case EndG:
        Machine->Change(new GameEnd());
        break;
    case PauseG:
        Machine->Push(new GamePause());

    case Quit:
        IsRunning = false;
        break;
        }
    }


}

void Game::Render()
{
    SDL_RenderClear(Renderer);

    Machine->Render();

    SDL_RenderPresent(Renderer);
}

void Game::Clean()
{

SDL_DestroyWindow(Window);

SDL_DestroyRenderer(Renderer);

while(Machine != NULL)
    {
        Machine->Popback();
    }

    delete Machine;

    SDL_Quit();
}
