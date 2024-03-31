#include "Game.h"
#include <bits/stdc++.h>

struct TileSet
{
    SDL_Texture* TexMap;
    int firstID;
    std::vector <SDL_Rect> SaveRect;
};

class Map
{
public:

    Map();

    ~Map();

    void Update();

    void loadTile(TileSet &tmp);

    void Render();

private:

    long long MapGame[5][51][81];
    TileSet Map_[7];
    SDL_Rect MapRect;

};
