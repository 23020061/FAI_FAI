#include "TextureManager.h"
#include <SDL_ttf.h>

SDL_Texture* TextureManager::LoadTexture(const char *FileName)
{

    SDL_Surface* tempSurface = IMG_Load(FileName);

    SDL_Texture* Tex = SDL_CreateTextureFromSurface(Game::Renderer, tempSurface);

    return Tex;
}

void TextureManager::Render( int x, int y, int mWidth, int mHeight, SDL_Texture* mTexture, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight};

	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx( Game::Renderer, mTexture, clip, &renderQuad, angle, center, flip );
}

SDL_Texture* TextureManager::LoadText(const char* NameTTF, const char* Content, int size_font, TTF_Font* gFont, SDL_Rect& TextRect)
{
     gFont = TTF_OpenFont(NameTTF, size_font);

     SDL_Color textColor = {139, 0, 0};

     SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, Content, textColor);

        TextRect.x = 0;
        TextRect.y = 0;
        TextRect.w = textSurface->w;
        TextRect.h = textSurface->h;

     SDL_Texture* temp = SDL_CreateTextureFromSurface(Game::Renderer, textSurface);

    return temp;
}
