#include "Game.h"
#include "Vector2D.h"
enum
{
    STATE_IDLE,
    STATE_MOVERUN,
    STATE_JUMP,
    STATE_FALL,
    STATE_GROUNDIMPACT,
    STATE_ATTACK,
    STATE_TAKINGDAMAGE,
    STATE_DEAD,
    STATE_SHIELDBLOCKING,
    STATE_TOTAL
};


class Character
{
public:
    Character(const char* Path, int x, int y);

    ~Character();
    void Fresh();

    void InputHandle(SDL_Event &event);

    void LoadSpriteState(int& cntState, const int& State, const int& STATE);

    void Move();

    void Update();

    void Render();

private:

    Vector2D Position;
    Vector2D Velocity;
    SDL_Texture* CharTex;
    SDL_Rect srcRect, destRect;

};

