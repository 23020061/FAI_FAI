#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* FileName)
{

    SDL_Surface* tempSurface = IMG_Load(FileName);

    SDL_Texture* Tex = SDL_CreateTextureFromSurface(Game::Renderer, tempSurface);

    return Tex;
}

void TextureManager::Render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{


}
