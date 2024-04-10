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


SDL_Renderer* Game::Renderer = nullptr;

Character* Player;
std::vector <Enemy1*> Enemy;
Uint8 CurrentState = Start;
StateMachine* CurrentMachine = nullptr;
Menu* menu;

MenuEnd* MenuExit;

Map* MAP;

Game::Game()
{
}
Game::~Game()
{
}
int GetRandom(int min, int max) {
    return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
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

    MenuExit = new MenuEnd();
    MenuExit->Init();

    MAP = new Map();
    Player = new Character("16x16 knight 3.png", 1600, 1600);
    Enemy.push_back(new Enemy1(400, 600));
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
        MenuExit->handle(Event);
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

    if(Player->Exit() == true)
    {
        CurrentMachine->Change(new GameEnd());
        CurrentState = End;
    }



    switch(CurrentState)
    {
        case Start:
        menu->Update();
        break;
        case In:
        Player->Update(MAP->HasCollision(), Enemy);
        while(Enemy.size() < 20)
        {
            int x, y;
            x = GetRandom(192, 2976);
            y = GetRandom(96, 3102);
            Enemy.push_back(new Enemy1(x, y));

        }

        for(int i = 0; i < Enemy.size(); i++)
        {
                Enemy[i]->Update(Player->getPosChar(), Player->GetPositionCam());
        }

        break;
        case End:
        MenuExit->Update();
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
        MAP->Render(Player->GetPositionCam());
        Player->Render();
        for(int i = 0; i < Enemy.size(); i++)
        {
            Enemy[i]->Render();
        }
        break;
        case End:
        MenuExit->Render();
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
