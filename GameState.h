#pragma once
enum
{
    Start = 0,
    Ingame = 1,
    End = 2
};

class GameState
{
public:

    virtual void Update();
    virtual void Render();

    virtual void Start();
    virtual void End();
    //virtual std::string getState(){return State;}

private:
    //static std::string State = "";

};
