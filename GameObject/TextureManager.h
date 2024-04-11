#pragma once

#include "Game.h"
#include <SDL_ttf.h>

class TextureManager
{
public:
    static SDL_Texture* LoadTexture(const char *FileName);

    static void Render( int x, int y, int mWidth, int mHeight, SDL_Texture* mTexture, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip );

    static SDL_Texture* LoadText(const char* NameTTF, const char* Content, int size_font, TTF_Font* gFont, SDL_Rect& TextRect);

private:



};
