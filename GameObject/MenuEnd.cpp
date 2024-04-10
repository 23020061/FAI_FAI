#include "Game.h"
#include "StateMachine.h"
#include "GameEnd.h"
#include "TextureManager.h"


void MenuEnd::Init()
{
    Play = new Button("play.png", 200, 200, 260, 95);
    Background = TextureManager::LoadTexture("background.png");
}

void MenuEnd::Update()
{
    Play->Update();

    if(Play->Enter() == true)
    {
        check = true;
    }
}

void MenuEnd::handle(SDL_Event &e)
{
    Play->handleEvent(e);
}

void MenuEnd::Render()
{
    SDL_RenderCopyEx(Game::Renderer, Background, NULL, NULL, 0, NULL, SDL_FLIP_NONE);

    Play->Render();
}
