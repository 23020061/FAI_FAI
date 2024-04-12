#include "Map.h"
#include "TextureManager.h"
#include <bits/stdc++.h>
#include "Character.h"

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

std::vector <int> IDhasCollision =
{
15 + 1, 16 + 1, 17 + 1,
    33 + 1, 34 + 1, 35 + 1,
    51 + 1, 52 + 1, 53 + 1,
    86 + 1, 87 + 1, 88 + 1, 89 + 1,
    104 + 1, 106 + 1, 107 + 1,
    122 + 1, 123 + 1, 124 + 1, 125 + 1,
    140 + 1, 141 + 1, 142 + 1, 143 + 1,
    0 + 181, 1 + 181, 2 + 181, 3 + 181, 4 + 181, 5 + 181, 6 + 181, 7 + 181, 8 + 181, 9 + 181, 10 + 181, 11 + 181, 12 + 181, 13 + 181, 14 + 181, 15 + 181, 16 + 181, 17 + 181, 18 + 181, 19 + 181, 20 + 181, 21 + 181, 22 + 181, 23 + 181, 24 + 181, 25 + 181, 26 + 181, 27 + 181, 28 + 181, 29 + 181, 30 + 181, 31 + 181, 32 + 181, 33 + 181,34 + 181, 35 + 181, 36 + 181, 37 + 181, 38 + 181, 39 + 181, 40 + 181, 41 + 181, 42 + 181, 43 + 181, 44 + 181, 45 + 181, 46 + 181, 47 + 181, 48 + 181, 49 + 181, 50 + 181, 51 + 181, 52 + 181, 53 + 181, 54 + 181, 55 + 181, 56 + 181, 57 + 181, 58 + 181, 59 + 181, 60 + 181, 61 + 181, 62 + 181, 63 + 181, 64 + 181, 65 + 181, 66 + 181, 67 + 181, 68 + 181, 69 + 181, 70 + 181, 71 + 181, 72 + 181, 73 + 181, 74 + 181, 75 + 181, 76 + 181, 77 + 181, 78 + 181, 79 + 181, 80 + 181, 81 + 181, 82 + 181, 83 + 181, 84 + 181, 85 + 181, 86 + 181, 87 + 181, 88 + 181, 89 + 181
};

std::vector <Collision> SaveCollisionMap;
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

                TileSprite[i][j][k] = new Tile(x, y, tmp);
                auto a = std::find(IDhasCollision.begin(), IDhasCollision.end(), tmp);
                if(a != IDhasCollision.end())
                {
                    Collision temp(x, y, TILE_WIDTH, TILE_HEIGHT);
                    SaveCollisionMap.push_back(temp);
                    //std::cout << tmp << ' ';
                }

                x += TILE_WIDTH;

                if(x >= MAP_WIDTH)
                {
                    y += TILE_HEIGHT;
                    x = 0;
                }
            }
            //std::cout << '\n';
        }
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

std::vector <Collision> Map::HasCollision()
{
    return SaveCollisionMap;
}

void Map::Destroy()
{
    SDL_DestroyTexture(Tex[0].Textile);
    SDL_DestroyTexture(Tex[1].Textile);
    while(IDhasCollision.size() > 0)
    {
        IDhasCollision.pop_back();
    }

    while(SaveCollisionMap.size() > 0)
    {
        SaveCollisionMap.pop_back();
    }

}

