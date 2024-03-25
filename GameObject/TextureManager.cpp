#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* FileName)
{

    SDL_Surface* tempSurface = IMG_Load(FileName);

    SDL_Texture* Tex = SDL_CreateTextureFromSurface(Game::Renderer, tempSurface);

    return Tex;
}
