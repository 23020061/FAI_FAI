#ifndef Game_h
#define Game_h

#include <SDL.h>
#include <SDL_image.h>
#include "iostream"

enum Game_State
{
    StartG = 0,
    In = 1,
    EndG = 2,
    PauseG = 3,
    Quit = 4
};

class Game
{
public:
    Game();
    ~Game();

    void init(const char* title, int x, int y, int Width, int Height, bool FullScreen);

    void HandleEvents();
    void Update();
    void Render();
    void Clean();

    static SDL_Renderer* Renderer;

    bool Running()
    {
        return IsRunning;
    }

private:
    bool IsRunning = true;
    SDL_Window* Window;
};

#endif // Game_h
