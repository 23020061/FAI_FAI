#pragma once

#include "Game.h"
#include "Collision.h"
#include "bits/stdc++.h"
struct TextureTile;

class Tile
{
public:
    Tile(int x, int y, int typeTile);

    void Render(TextureTile* tmp, SDL_Rect &Camera);

    int getType()
    {
        return mType;
    }

    SDL_Rect getBox()
    {
        return mBox;
    }

private:

    SDL_Rect mBox;

    int mType;

};

struct TextureTile
{
    SDL_Texture* Textile;
    int firstID;
    SDL_Rect TileClip[1000];
};

class Map
{
  public:

    Map();

    void UpdateTile(TextureTile &tmp);

    void Render(SDL_Rect camera);

    std::vector <Collision> HasCollision();

  private:

    int TOTAL = 2;

    TextureTile Tex[2];

    int layer = 4, Rect_Width = 100, Rect_Height = 100 ;

    Tile* TileSprite[4][3201][3201];

};
