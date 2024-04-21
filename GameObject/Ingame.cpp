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
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );

    Music = Mix_LoadMUS("11-Fight2.mp3");
    MAP = new Map();

    Player = new Character("16x16 knight 1.png", 1600, 1600);

    Enemy1_.push_back(new Enemy1(GetRandom(192, 2976), GetRandom(96, 3102)));

    Enemy2_.push_back(new Enemy2(GetRandom(192, 2976), GetRandom(96, 3102)));

    Mix_PlayMusic(Music, -1);

    return true;
}

bool Ingame::End()
{
    delete Player;
    while(Enemy1_.size() > 0)
    {
        delete Enemy1_.back();
        Enemy1_.pop_back();
    }

    Enemy1_.clear();

        while(Enemy2_.size() > 0)
    {
        delete Enemy2_.back();
        Enemy2_.pop_back();
    }

    Enemy1_.clear();

    MAP->Destroy();
    //delete MAP;
    return true;
    Mix_Quit();
}

void Ingame::Update(int &CurrentState, int &checkChange)
{
        if(Player->EnterP() == true)
        {

            CurrentState = PauseG;
            checkChange = 1;
        }
        else
        {
        Player->Update(MAP->HasCollision(), Enemy1_, Enemy2_);

        while(Enemy1_.size() < 10 )
        {
           int x, y;
        x = GetRandom(192, 2976);
           y = GetRandom(96, 3102);
            Enemy1_.push_back(new Enemy1(x, y));
       }

        for(int i = 0; i < Enemy1_.size(); i++)
        {
            Enemy1_[i]->Update(Player->getPosChar(), Player->GetColli(), Player->GetPositionCam());
            if( Enemy1_[i]->checkDead == true)
            {
                delete Enemy1_[i];
                Enemy1_.erase(Enemy1_.begin() + i);
                i--;
            }
        }

                while(Enemy2_.size() < 10)
        {
            int x, y;
            x = GetRandom(192, 2976);
            y = GetRandom(96, 3102);
            Enemy2_.push_back(new Enemy2(x, y));
        }

        for(int i = 0; i < Enemy2_.size(); i++)
        {
            Enemy2_[i]->Update(Player->getPosChar(), Player->GetColli(), Player->GetPositionCam());
            if( Enemy2_[i]->checkDead == true)
            {
                delete Enemy2_[i];
                Enemy2_.erase(Enemy2_.begin() + i);
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

}

void Ingame::Render()
{
        MAP->Render(Player->GetPositionCam());

        for(int i = 0; i < Enemy1_.size(); i++)
        {
            Enemy1_[i]->Render();
        }


        for(int i = 0; i < Enemy2_.size(); i++)
        {
            Enemy2_[i]->Render();
        }

        Player->Render();



}

void Ingame::Handle(SDL_Event& Event)
{
        Player->InputHandle(Event);
}
