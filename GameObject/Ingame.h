#include "Game.h"
#include "GameState.h"

class Ingame : public GameState
{
public:

    virtual bool Start();
    virtual bool End();
    virtual void Update();
    virtual void Render();
    virtual std::string getState() const
    {
        return GameIn;
    }
private:
    static const std::string GameIn;

};
