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
std::string ScoreMain = "";
std::string Name_;

int HighScore = 0;
bool changeMain = false;
std::string HighName = " ";

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
    if(changeMain == true) HighName = Name_;

    if(CurrentState == EndG)
        {
            Machine->Update(CurrentState, checkChange, ScoreMain, HighName, HighScore, changeMain);
        }
    else
        {
            Machine->Update(CurrentState, checkChange, ScoreMain, Name_, HighScore, changeMain);
        }

    if(checkChange == 1 )
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
        break;
    case Quit:
        IsRunning = false;
        break;
        }
    }
    if(checkChange == 2)
    {
    Machine->Popback();
    }


}

void Game::Render()
{
    SDL_RenderClear(Renderer);
switch(CurrentState)
{
    case PauseG:
    Machine->Render(2);
    break;
    default:
    Machine->Render(1);
    break;
}

    SDL_RenderPresent(Renderer);
}

void Game::Clean()
{

while(Machine != NULL)
    {
        Machine->Popback();
    }
    delete Machine;

SDL_DestroyWindow(Window);
delete Window;

SDL_DestroyRenderer(Renderer);
delete Renderer;

    SDL_Quit();
}
