#pragma once

#include "Game.h"
#include "Vector2D.h"
#include <SDL_ttf.h>

enum ButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_IN = 1,
    BUTTON_SPRITE_MOUSE_TOTAL = 2
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
    SDL_Texture* TextureText;

    SDL_Rect PosButton;
    SDL_Rect PosButton1;
    SDL_Rect PosButton2;

    bool check = false;
    std::string text = "";
    TTF_Font* gFont = NULL;
    SDL_Rect TextButton;
};
