#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* FileName)
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
