#include "GameState.h"

class GameStart : public GameState
{
public:
    virtual bool Start();
    virtual bool End();

    virtual void Update();
    virtual void Render();

    virtual std::string getState() const
    {
        return StartGame;
    }

private:

    static const std::string StartGame;

};
