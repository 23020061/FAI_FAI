#include "GameStart.h"

class GameStart : public GameState
{
public:
    virtual void Start();
    virtual void End();

    virtual void Update();
    virtual void Render();

    virtual void std::string getState()
    {
        return Start;
    }

private:

    static const std::string Start = "Start";

};
