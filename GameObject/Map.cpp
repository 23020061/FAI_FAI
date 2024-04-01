#include "Map.h"
#include "TextureManager.h"
#include <bits/stdc++.h>
#include "Character.h"

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

Tile::Tile(int x, int y, int typeTile)
{
    mBox.x = x;

    mBox.y = y;

    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    mType = typeTile;
}

void Tile::Render(TextureTile* tmp ,SDL_Rect& Camera)
{
    int x = 1;
    while(x < 2)
    {
        if(mType < tmp[x].firstID)
        {
            TextureManager::Render((mBox.x - Camera.x), (mBox.y - Camera.y) , mBox.w, mBox.h, tmp[x - 1].Textile, &tmp[x - 1].TileClip[mType - tmp[x - 1].firstID + 1], 0, NULL, SDL_FLIP_NONE);
            break;
        }
        else
            x++;
    }
    if(mType > tmp[x - 1].firstID)
    {
        TextureManager::Render((mBox.x - Camera.x), (mBox.y - Camera.y) , mBox.w, mBox.h, tmp[x - 1].Textile, &tmp[x - 1].TileClip[mType - tmp[x - 1].firstID + 1], 0, NULL, SDL_FLIP_NONE);
    }

}

Map::Map()
{
    Tex[0].Textile = TextureManager::LoadTexture("volcanoe_tiles.png");
    Tex[1].Textile = TextureManager::LoadTexture("volcanoe_assets.png");

    Tex[0].firstID = 1;
    Tex[1].firstID = 181;

    for(int i = 0; i < TOTAL; i++)
    {
        //std:: cout << i << '\n';
        UpdateTile(Tex[i]);
    }

    std::ifstream fi("Map.txt");

    for(int i = 0; i < layer; i++)
    {
        int x = 0, y = 0;
        for(int j = 0; j < Rect_Height; j++)
        {
            long long tmp ;
            for(int k = 0; k < Rect_Width; k++)
            {
                fi >> tmp;
                std::cout << tmp << ' ';
                //if(tmp == -1) tmp = 0;
                TileSprite[i][j][k] = new Tile(x, y, tmp);

                x += TILE_WIDTH;

                if(x >= MAP_WIDTH)
                {
                    y += TILE_HEIGHT;
                    x = 0;
                }
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
}

void Map::UpdateTile(TextureTile &tmp)
{
    int width = 0, height = 0;

    SDL_QueryTexture(tmp.Textile, NULL, NULL, &width, &height);
    //std::cout << width << ';' << height << '\n';
    int cnt = 1;
    for(int j = 0; j < height; j += TILE_HEIGHT)
    {
        for(int i = 0; i < width; i += TILE_WIDTH)
        {
            tmp.TileClip[cnt].x = i;
            tmp.TileClip[cnt].y = j;
            tmp.TileClip[cnt].w = TILE_WIDTH;
            tmp.TileClip[cnt].h = TILE_HEIGHT;
            cnt++;
        }
    }
   // std::cout << cnt - 1 << '\n';
}

void Map::Render(SDL_Rect camera)
{
   for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < Rect_Height; j++)
        {
            for(int k = 0; k < Rect_Width; k++)
            {
                TileSprite[i][j][k]->Render(Tex, camera);
            }
        }

    }
}
