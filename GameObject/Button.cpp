#include "Button.h"
#include "TextureManager.h"
#include "StateMachine.h"

float Zoom = 1.25;

Button::Button(std::string path, int x, int y, int w, int h)
{
    TextureButton = TextureManager::LoadTexture("play.png");

    Position.x = x;
    Position.y = y;

    PosButton2.x = Position.x;
    PosButton2.y = Position.y;
    PosButton2.w = w;
    PosButton2.h = h;

    PosButton1.x = Position.x - w * ((Zoom - 1) / 2);
    PosButton1.y = Position.y - h * ((Zoom - 1) / 2);
    PosButton1.w = w * Zoom;
    PosButton1.h = h * Zoom;

    PosButton = PosButton2;

}

void Button::handleEvent(SDL_Event& e)
{
	if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool inside = true;

		if( x < Position.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > Position.x + PosButton.w )
		{
			inside = false;
		}
		else if( y < Position.y )
		{
			inside = false;
		}
		else if( y > Position.y + PosButton.h )
		{
			inside = false;
		}

		if( !inside )
		{
			CurrentButton = BUTTON_SPRITE_MOUSE_OUT;
		}
		else
		{
			//Set mouse over sprite
			switch( e.type )
			{
				case SDL_MOUSEMOTION:
                CurrentButton = BUTTON_SPRITE_MOUSE_IN;
                break;
				case SDL_MOUSEBUTTONDOWN:
                check = true;
                CurrentButton = BUTTON_SPRITE_MOUSE_IN;
                break;
				case SDL_MOUSEBUTTONUP:
				CurrentButton = BUTTON_SPRITE_MOUSE_IN;
				break;
			}
		}
    }
}

void Button::Update()
{
    if(CurrentButton == BUTTON_SPRITE_MOUSE_IN)
    {
        PosButton = PosButton1;
    }
    else
    {
        PosButton = PosButton2;
    }
}

void Button::Render()
{
    SDL_RenderCopyEx(Game::Renderer, TextureButton, NULL, &PosButton, 0, NULL, SDL_FLIP_NONE);
}
