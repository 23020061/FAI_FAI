#pragma once

#include "Game.h"
#include "Vector2D.h"

enum ButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT,
    BUTTON_SPRITE_MOUSE_IN,
    BUTTON_SPRITE_MOUSE_TOTAL
};

class Button
{
public:
    Button(std::string path, int x, int y, int w, int h);

    ~Button();

    void handleEvent(SDL_Event &e);

    void Render();

    void Update();

    bool Enter()
    {
        return check;
    }

private:
    Vector2D Position;

    ButtonSprite CurrentButton;

    SDL_Texture* TextureButton;

    SDL_Rect PosButton;
    SDL_Rect PosButton1;
    SDL_Rect PosButton2;

    bool check = false;

};
