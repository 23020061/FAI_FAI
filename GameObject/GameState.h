#pragma once

class GameState
{
public:

    virtual void Update();
    virtual void Render();

    virtual void Start();
    virtual void End();
    virtual std::string getState(){return State;}

private:
    static std::string State = "";

};
