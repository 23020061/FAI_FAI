#include "Map.h"
#include <bits/stdc++.h>
#include "TextureManager.h"

const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;

Map::Map()
{
    std::ifstream fi("Map.txt");

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 50; j++)
        {
            for(int k = 0; k < 80; k++)
            {
                fi>>MapGame[i][j][k];
                //std::cout << MapGame[i][j][k] << ' ';
            }
             //std::cout << '\n';
        }
         //std::cout << '\n';
    }

    Map_[0].TexMap = TextureManager::LoadTexture("Details.png");
    Map_[1].TexMap = TextureManager::LoadTexture("Port Town Free.png");
    Map_[2].TexMap = TextureManager::LoadTexture("Con House 1.png");
    Map_[3].TexMap = TextureManager::LoadTexture("Buildings.png");
    Map_[4].TexMap = TextureManager::LoadTexture("Props.png");
    Map_[5].TexMap = TextureManager::LoadTexture("Tileset_RockSlope.png");
    Map_[6].TexMap = TextureManager::LoadTexture("Adventure Awaits Asset Pack 1.0.png");
    Map_[0].firstID = 1;
    Map_[1].firstID = 415;
    Map_[2].firstID = 685;
    Map_[3].firstID = 945;
    Map_[4].firstID = 1387;
    Map_[5].firstID = 1567;
    Map_[6].firstID = 5663;

        for(int i = 0; i < 7; i++)
    {
        loadTile(Map_[i]);
    }
}

void Map::loadTile(TileSet &tmp)
{
    int width = 0, height = 0;

    SDL_Texture* temp = tmp.TexMap;
    SDL_QueryTexture(temp, NULL, NULL, &width, &height);
    std:: cout << width << ' ' << height << '\n';
    int cnt_width = 0, cnt_height = 0;
    cnt_width -= TILE_WIDTH;
    for(int i = 0; i < (width * height) / (TILE_WIDTH * TILE_HEIGHT); i++)
    {

        if(cnt_width >= width - TILE_WIDTH)
        {
            cnt_height += TILE_HEIGHT;
            cnt_width = 0;
        }
        else
        {
            cnt_width += TILE_WIDTH;
        }

        SDL_Rect x = {cnt_width, cnt_height, TILE_WIDTH, TILE_HEIGHT};
        //std::cout << i << ' ';
        //std::cout << cnt_width << ' ' << cnt_height << '\n';
        tmp.SaveRect.push_back(x);
    }
    //std::cout << '\n';
}

void Map::Update()
{

}

void Map::Render()
{

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 50; j++)
        {
            for(int k = 0; k < 80; k++)
            {
                MapRect.x = k * TILE_WIDTH * 2;
                MapRect.y = j * TILE_HEIGHT * 2;
                MapRect.w = TILE_WIDTH * 2;
                MapRect.h = TILE_HEIGHT * 2;

                //std::cout << "(" << MapRect.x << ";" << MapRect.y << ")" << '\n';
                if(MapGame[i][j][k] != 0)
                {
                    int x = 1;
                    while(x <= 7)
                    {
                        if(MapGame[i][j][k] < Map_[x].firstID)
                        {
                            SDL_RenderCopyEx(Game::Renderer, Map_[x - 1].TexMap, &Map_[x - 1].SaveRect[MapGame[i][j][k] - Map_[x - 1].firstID], &MapRect, 0, NULL, SDL_FLIP_NONE );
                            //SDL_RenderCopyEx(Game::Renderer, Map_[x - 1].TexMap, NULL, NULL, 0, NULL, SDL_FLIP_NONE);
                            break;
                        }
                        else
                        {
                            x++;
                        }
                    }
                }
            }
        }
    }
}
