#include "Game.h"

#include <bits/stdc++.h>

Game* game = nullptr;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;


int main(int argc, char* argv[])
{
    const int FPS = 25;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;

    int frameTime;

    game = new Game();

    game->init("FAI FAI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    while(game->Running() == true)
    {
        frameStart = SDL_GetTicks();

        game->HandleEvents();

        game->Update();

        game->Render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
      game->Clean();
    return 0;


}

