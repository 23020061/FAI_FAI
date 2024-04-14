#include "Ingame.h"
#include "Game.h"
#include "Character.h"
#include "Vector2D.h"
#include "Map.h"

const std::string Ingame::GameIn = "InGame";







int GetRandom(int min, int max)
{
    return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}
bool Ingame::Start()
{
    MAP = new Map();
    Player = new Character("16x16 knight 1.png", 1600, 1600);
    Enemy.push_back(new Enemy1(400, 600));
    return true;
}

bool Ingame::End()
{
    delete Player;
    while(Enemy.size() > 0)
    {
        delete Enemy.back();
        Enemy.pop_back();
    }

    Enemy.clear();

    MAP->Destroy();
    //delete MAP;
    return true;
}

void Ingame::Update(int &CurrentState, int &checkChange)
{
        Player->Update(MAP->HasCollision(), Enemy);
        while(Enemy.size() < 40 )
        {
            int x, y;
            x = GetRandom(192, 2976);
            y = GetRandom(96, 3102);
            Enemy.push_back(new Enemy1(x, y));
        }

        for(int i = 0; i < Enemy.size(); i++)
        {
            Enemy[i]->Update(Player->getPosChar(), Player->GetColli(), Player->GetPositionCam());
            if(Enemy[i]->HealthEnemy <= 0)
            {
                delete Enemy[i];
                Enemy.erase(Enemy.begin() + i);
                i--;
            }
        }

        if(Player->Exit() == true)
        {
            End();
            CurrentState = EndG;
            checkChange = 1;
        }

}

void Ingame::Render()
{
        MAP->Render(Player->GetPositionCam());

        for(int i = 0; i < Enemy.size(); i++)
        {
            Enemy[i]->Render();
        }

        Player->Render();



}

void Ingame::Handle(SDL_Event& Event)
{
        Player->InputHandle(Event);
}
