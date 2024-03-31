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

const int MAP_WIDTH = 2560;
const int MAP_HEIGHT = 1440;
const int CAM_WIDTH = 1280;
const int CAM_HEIGHT = 720;

class Character
{
public:
    Character(const char* Path, int x, int y);

    ~Character();

    void Fresh();

    const Uint8* CurrentKeyState = SDL_GetKeyboardState(NULL);

    void InputHandle(SDL_Event &event);

    void LoadSpriteState(int& cntState, const int& State, const int& STATE);

    void Move();

    void Camera();

    void Update();

    void Render();

private:

    Vector2D Position;
    Vector2D Velocity;
    SDL_Texture* CharTex;
    SDL_Texture* MapTex;
    SDL_Rect srcRect, destRect;
    SDL_Rect Cam, Cam_tmp;

};

