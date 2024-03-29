#include "Game.h"

class TextureManager
{
public:
    static SDL_Texture* LoadTexture(const char* FileName);

    static void Render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip );

private:

};
