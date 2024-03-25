#include "Game.h"
#include <bits/stdc++.h>

Game* game = nullptr;

int main(int argc, char* argv[])
{
    const int FPS = 25;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();

    game->init("FAI FAI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 800, 0);

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

