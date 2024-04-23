#include "Character.h"
#include "TextureManager.h"
#include "Map.h"
#include "Collision.h"
#include "Enemy.h"

int IDLE = 5, cntIDLE = 0,
    MOVERUN = 8, cntMOVERUN = 0,
    JUMP = 3, cntJump = 0,
    FALL = 1, cntFALL = 0,
    GROUNDIMPACT = 2, cntGROUNDIMPACT = 0,
    ATTACK = 3, cntATTACK = 0,
    TAKINGDAMAGE = 1, cntTAKINGDAMAGE = 0,
    DEAD = 6, cntDEAD = 0,
    SHIELDBLOCKING = 2, cntSHEILDBLOCKING = 0;

SDL_Rect Sprite[STATE_TOTAL][10];
SDL_Rect Current;
SDL_RendererFlip Check = SDL_FLIP_NONE;
 float CHARACTER_VEL = 7;

const int CHAR_WIDTH = 64;
const int CHAR_HEIGHT = 64;


Collision ColliChar(1600 + 54, 1600 + 58, 25 * 2, 19 * 2);

Collision Knight(ColliChar.getCollisionBox().x - 35 * 2, ColliChar.getCollisionBox().y - 28 * 2,  27 * 2, 21 * 2);



Character::Character(const char* path,int x, int y)
{
    CharTex = TextureManager::LoadTexture(path);


    Cam.x = (Position.x + CHAR_WIDTH / 2) - CAM_WIDTH / 2;
    Cam.y = (Position.y + CHAR_HEIGHT / 2) - CAM_HEIGHT / 2;


    Health_Char = 100;

    TTF_Init();

    check = false;

    Position.x = x;
    Position.y = y;

    IconHealth = TextureManager::LoadTexture("health.png");

    HealthLeft = TextureManager::LoadTexture("HealthLeft.png");
    HealthHolderLeft = TextureManager::LoadTexture("HealthHolderLeft.png");

    HealthRight = TextureManager::LoadTexture("HealthRight.png");
    HealthHolderRight = TextureManager::LoadTexture("HealthHolderRight.png");

    HealthCenter = TextureManager::LoadTexture("HealthCenter.png");
    HealthHolderCenter = TextureManager::LoadTexture("HealthHolderCenter.png");

    IconExp = TextureManager::LoadTexture("Exp.png");

    ExpLeft = TextureManager::LoadTexture("ExpLeft.png");
    ExpHolderLeft = TextureManager::LoadTexture("ExpHolderLeft.png");

    ExpRight = TextureManager::LoadTexture("ExpRight.png");
    ExpHolderRight = TextureManager::LoadTexture("ExpHolderRight.png");

    ExpCenter = TextureManager::LoadTexture("ExpCenter.png");
    ExpHolderCenter = TextureManager::LoadTexture("ExpHolderCenter.png");

    ButtonAttack = TextureManager::LoadTexture("ButtonAttack.png");
    TimeCoolDownAttack = TextureManager::LoadTexture("Xam.jpg");
    TimeAttack.x = 1100;
    TimeAttack.y = 680;
    TimeAttack.w = 60;
    TimeAttack.h = 60;

    MoveCharacter = TextureManager::LoadTexture("None.png");

    Cam.w = CAM_WIDTH;
    Cam.h = CAM_HEIGHT;

    EffectRun = TextureManager::LoadTexture("RunEffect.png");

    for(int i = 0; i < STATE_TOTAL; i++)
    {
        int tmp;
        switch(i)
        {
        case 0:
            tmp = IDLE;
            break;
        case 1:
            tmp = MOVERUN;
            break;
        case 2:
            tmp = JUMP;
            break;
        case 3:
            tmp = FALL;
            break;
        case 4:
            tmp = GROUNDIMPACT;
            break;
        case 5:
            tmp = ATTACK;
            break;
        case 6:
            tmp = TAKINGDAMAGE;
            break;
        case 7:
            tmp = DEAD;
            break;
        case 8:
            tmp = SHIELDBLOCKING;
            break;
        }

        for(int j = 0; j < tmp; j++)
        {
            Sprite[i][j].x = CHAR_WIDTH * j;
            Sprite[i][j].y = CHAR_HEIGHT * i;
            Sprite[i][j].w = CHAR_WIDTH;
            Sprite[i][j].h = CHAR_HEIGHT;
        }
    }

    for(int i = 0; i < TotalEffectRun; i++)
    {
        RunRect[i].x = i * 64;
        RunRect[i].y = 0;
        RunRect[i].w = 64;
        RunRect[i].h = 20;
    }


}

Collision Character::GetColli()
{
    return ColliChar;
}


void Character::Move(const std::vector<Collision> &MapColli)
{
    Position.x += Velocity.x;
    ColliChar.UpdateX(Position.x + 48);
    bool checkCharX = false;

    for(int i = 0; i < MapColli.size(); i++)
    {
       if(ColliChar.checkCollision(MapColli[i]) == true && checkCharX == false)
        {
            checkCharX = true;
            break;
        }
    }

    if((Position.x < 0) || (Position.x > MAP_WIDTH - CHAR_WIDTH * 2) || checkCharX == true)
    {
        Position.x -= Velocity.x;
    }

    Position.y += Velocity.y;

    ColliChar.UpdateY(Position.y + 58);

    bool checkCharY = false;

    for(int i = 0; i < (int)MapColli.size(); i++)
    {
    if(ColliChar.checkCollision(MapColli[i]))
        {
            checkCharY = true;
        }
    }
    if((Position.y < 0) || (Position.y > MAP_HEIGHT - CHAR_HEIGHT * 2) || checkCharY == true)
    {
        Position.y -= Velocity.y;
    }

    ColliChar.UpdateW(14 * 2);
    ColliChar.UpdateH(19 * 2);
}


void Character::Fresh()
{
    cntIDLE = 0;
    cntMOVERUN = 0;
    cntJump = 0;
    cntFALL = 0;
    cntGROUNDIMPACT = 0;
    cntATTACK = 0;
    cntTAKINGDAMAGE = 0;
    cntDEAD = 0;
    cntSHEILDBLOCKING = 0;
}
void Character::LoadSpriteState(int& cntState, const int& State, const int& STATE)
{
    int temp;
    temp = cntState;
    Fresh();
    cntState = temp;
    cntState++;
    if(cntState >= State) cntState = 0;
    Current = Sprite[STATE][cntState];
}

void Character::InputHandle(SDL_Event& event)
{
        Velocity.x = 0;
        Velocity.y = 0;
        Uint32 StartTime = SDL_GetTicks();

        if(StartTime - CurrentTime <= 1000)
        {
            TimeAttack.w = (60 * 1000 - 60 *( (StartTime - CurrentTime))) / 1000;
        }
        else
        {
            TimeAttack.w = 0;
        }
    if(Health_Char > 0)
    {
        checkP = false;
            if(CurrentKeyState[SDL_SCANCODE_LSHIFT])
            {
                checkEffectRun = true;
                cntEffectRun++;
                if(cntEffectRun == TotalEffectRun) cntEffectRun = 0;
                CHARACTER_VEL = 6.5 * 2;
                inShift = true;
            }
            else
            {
                checkEffectRun = false;
                inShift = false;
                CHARACTER_VEL = 6.5;
            }
            if(CurrentKeyState[SDL_SCANCODE_P]) checkP = true;
            if(CurrentKeyState[SDL_SCANCODE_J] && StartTime - CurrentTime >= 1000  )
        {

            if(StartTime - CurrentTime >= 1000 || CoolDownAttack == true)
            {
                LoadSpriteState(cntATTACK, ATTACK, STATE_ATTACK);
                CoolDownAttack = true;

                if(cntATTACK == 0)
                {
                    CurrentTime = StartTime;
                    CoolDownAttack = false;
                }
            }
        }
        else if(CurrentKeyState[SDL_SCANCODE_K])
        {
            if(cntSHEILDBLOCKING == 1) cntSHEILDBLOCKING--;
            LoadSpriteState(cntSHEILDBLOCKING, SHIELDBLOCKING, STATE_SHIELDBLOCKING);
        }
        else
        {
            bool state = false;
            if(CurrentKeyState[SDL_SCANCODE_D])
        {
            state = true;
            Check = SDL_FLIP_NONE;
            LoadSpriteState(cntMOVERUN, MOVERUN, STATE_MOVERUN);
            Velocity.x += CHARACTER_VEL;
            MoveCharacter = TextureManager::LoadTexture("Right.png");
        } else if(CurrentKeyState[SDL_SCANCODE_A])
        {
            state = true;
            Check = SDL_FLIP_HORIZONTAL;
            LoadSpriteState(cntMOVERUN, MOVERUN, STATE_MOVERUN);
            Velocity.x -= CHARACTER_VEL;
            MoveCharacter = TextureManager::LoadTexture("Left.png");

        }
            else if(CurrentKeyState[SDL_SCANCODE_S])
        {
            state = true;
            LoadSpriteState(cntMOVERUN, MOVERUN, STATE_MOVERUN);
            Velocity.y += CHARACTER_VEL;
            MoveCharacter = TextureManager::LoadTexture("Bottom.png");

        }
        else if(CurrentKeyState[SDL_SCANCODE_W])
        {
            state = true;
            LoadSpriteState(cntMOVERUN, MOVERUN, STATE_MOVERUN);
            Velocity.y -= CHARACTER_VEL;
            MoveCharacter = TextureManager::LoadTexture("Top.png");
        }
        else
        {
            MoveCharacter = TextureManager::LoadTexture("None.png");
            checkEffectRun = false;
        }

        if(state == false)
        {
            LoadSpriteState(cntIDLE, IDLE, STATE_IDLE);
        }

        }
    }
}

void Character::Camera()
{
    Cam.x = (Position.x + CHAR_WIDTH / 2) - CAM_WIDTH / 2;
    Cam.y = (Position.y + CHAR_HEIGHT / 2) - CAM_HEIGHT / 2;

    if(Cam.x < 0)
    {
        Cam.x = 0;
    }
    if(Cam.y < 0)
    {
        Cam.y = 0;
    }

    if(Cam.x > MAP_WIDTH - CAM_WIDTH)
    {
        Cam.x = MAP_WIDTH - CAM_WIDTH;
    }

    if(Cam.y > MAP_HEIGHT - CAM_HEIGHT)
    {
        Cam.y = MAP_HEIGHT - CAM_HEIGHT;
    }

}

void Character::Update(std::vector <Collision> MapColli, std::vector<Enemy1*> &Enemy, std::vector <Enemy2*> &EnemyOther)
{
    Move(MapColli);

   // std::cout << ColliChar.getCollisionBox().x << ";" << ColliChar.getCollisionBox().y << '\t' << ColliChar.getCollisionBox().w << ";" << ColliChar.getCollisionBox().h << '\n';
        if(Check == SDL_FLIP_NONE)
        {
            Knight.UpdateX(Position.x + 27 * 2);
            Knight.UpdateY(Position.y + 22 * 2);
            Knight.UpdateW(29 * 2);
            Knight.UpdateH(26 * 2);
        }
        else
        {
            Knight.UpdateX(Position.x + 8 * 2);
            Knight.UpdateY(Position.y + 22 * 2);
            Knight.UpdateW(29 * 2);
            Knight.UpdateH(26 * 2);
        }
    for(int i = 0; i < (int) Enemy.size(); i++)
    {
        if(Enemy[i]->attack_enemy == true)
    {
      Health_Char -= (1.0 / Armor);
    }
        if(CurrentKeyState[SDL_SCANCODE_J] && Knight.checkCollision(Enemy[i]->getColli()) == true)
        {
            //std::cout << Position.x << ";" << Position.y << '\n';
            //std::cout << Knight.getCollisionBox().x << ";" << Knight.getCollisionBox().y << ' ' << Knight.getCollisionBox().w << ";" << Knight.getCollisionBox().h << '\n';
            if(cntATTACK == ATTACK - 1)
            {
                Enemy[i]->HealthEnemy -= 2;
                //std::cout << Enemy[i]->Health << '\n';
                Enemy[i]->checkHealth = true;
                if(Enemy[i]->HealthEnemy == 0)
                {
                    Exp_Char += 10;
                    Score += 10;
                }
            }
        }
    else
        {
                checkAttack = 0;
        }
    }
    ColliChar.UpdateH(22 * 2);
    ColliChar.UpdateW(11 * 2);
    ColliChar.UpdateX(Position.x + 26 * 2);
    ColliChar.UpdateY(Position.y + 26 * 2);

        for(int i = 0; i < (int) EnemyOther.size(); i++)
    {
        if(EnemyOther[i]->attack_enemy == true && ColliChar.checkCollision(EnemyOther[i]->getColli()) == true)
        {
      Health_Char -= (10 / Armor);
        }

        if(CurrentKeyState[SDL_SCANCODE_J] && Knight.checkCollision(EnemyOther[i]->getColli()) == true)
        {
            //std::cout << Position.x << ";" << Position.y << '\n';
            //std::cout << Knight.getCollisionBox().x << ";" << Knight.getCollisionBox().y << ' ' << Knight.getCollisionBox().w << ";" << Knight.getCollisionBox().h << '\n';
            if(cntATTACK == ATTACK - 1)
            {
                EnemyOther[i]->HealthEnemy -= 2;
                //std::cout << Enemy[i]->Health << '\n';
                EnemyOther[i]->checkHealth = true;
                if(EnemyOther[i]->HealthEnemy == 0)
                {
                    Exp_Char += 15;
                    Score += 15;
                }
            }
        }
    else
        {
                checkAttackOther = 0;
        }


    }

        if(Health_Char <= 0)
    {
        checkDead++;
        LoadSpriteState(cntDEAD, DEAD, STATE_DEAD);
        SDL_Delay(100);
        if(checkDead == DEAD)
        {
            check = true;
            SDL_DestroyTexture(CharTex);
        }
    }

    Camera();

    srcRect.x  = Position.x - Cam.x;
    srcRect.y  = Position.y - Cam.y;

    srcRect.w = CHAR_WIDTH * 2;
    srcRect.h = CHAR_HEIGHT * 2;

    std::string s = std::to_string(Score);
    total = ScoreChar + s;
    TexScore = TextureManager::LoadText("monogram.ttf", total.c_str(), 40, ScoreFont, RectScore);
   // std::cout << total << '\n';

   if(Check == SDL_FLIP_NONE)
   {
       checkFlipRun = SDL_FLIP_HORIZONTAL;
        Allow.x = (Position.x - Cam.x + 26 * 2 - 64);
        Allow.y = (Position.y - Cam.y + 48 * 2 - 20);
        Allow.w = 64;
        Allow.h = 20;
   }
   else
   {
       checkFlipRun = SDL_FLIP_NONE;
        Allow.x = (Position.x - Cam.x + 64 * 2 - 26 * 2);
        Allow.y = (Position.y - Cam.y + 48 * 2 - 20);
        Allow.w = 64;
        Allow.h = 20;
   }
}

void Character::Render()
{

   {
    TextureManager::Render(10, 10, 34, 30, IconHealth, NULL, 0, NULL, SDL_FLIP_NONE);

    TextureManager::Render(50, 10, 206 / 10, 349 / 10, HealthHolderLeft, NULL, 0, NULL, SDL_FLIP_NONE);
    for(int i = 10; i <= 90; i++)
    {
        TextureManager::Render(50 + 206 / 10 + (i - 10) * 22 / 11, 10, 220 / 100, 349 / 10, HealthHolderCenter, NULL, 0, NULL, SDL_FLIP_NONE);
    }
    TextureManager::Render(50 + 206 / 10 + 80 * 22 / 11, 10, 206 / 10, 349 / 10, HealthHolderRight, NULL, 0, NULL, SDL_FLIP_NONE);

    TextureManager::Render(50, 10, 206 / 10, 349 / 10, HealthLeft, NULL, 0, NULL, SDL_FLIP_NONE);

    for(int i = 10; i <= Health_Char - 10; i++)
    {
        TextureManager::Render(50 + 206 / 10 + (i - 10) * 22 / 11, 10, 22 / 10, 349 / 10, HealthCenter, NULL, 0, NULL, SDL_FLIP_NONE);
    }

    if(Health_Char == 100)
    {
        TextureManager::Render(50 + 206 / 10 + 80 * 22 / 11, 10, 206 / 10, 349 / 10, HealthRight, NULL, 0, NULL, SDL_FLIP_NONE);
    }

    }


    {

    TextureManager::Render(10, 40, 34, 30, IconExp, NULL, 0, NULL, SDL_FLIP_NONE);

    TextureManager::Render(50, 40, 206 / 10, 349 / 10, ExpHolderLeft, NULL, 0, NULL, SDL_FLIP_NONE);
    for(int i = 10; i <= 90; i++)
    {
        TextureManager::Render(50 + 206 / 10 + (i - 10) * 22 / 11, 40, 220 / 100, 349 / 10, ExpHolderCenter, NULL, 0, NULL, SDL_FLIP_NONE);
    }
    TextureManager::Render(50 + 206 / 10 + 80 * 22 / 11, 40, 206 / 10, 349 / 10, ExpHolderRight, NULL, 0, NULL, SDL_FLIP_NONE);

    TextureManager::Render(50, 40, 206 / 10, 349 / 10, ExpLeft, NULL, 0, NULL, SDL_FLIP_NONE);

    for(int i = 10; i <= Exp_Char - 10; i++)
    {
        TextureManager::Render(50 + 206 / 10 + (i - 10) * 22 / 11, 40, 22 / 10, 349 / 10, ExpCenter, NULL, 0, NULL, SDL_FLIP_NONE);
    }

    if(Exp_Char == 100)
    {
        TextureManager::Render(50 + 206 / 10 + 80 * 22 / 11, 40, 206 / 10, 349 / 10, ExpRight, NULL, 0, NULL, SDL_FLIP_NONE);
    }

    }
    if(Exp_Char >= 100)
    {   if(cntPath <= 3) cntPath++;
        switch(cntPath)
        {
            case 2:
                CharTex = TextureManager::LoadTexture("16x16 knight 2.png");
                Health_Char = 100;
                Armor += 2;
                break;
            case 3:
                CharTex = TextureManager::LoadTexture("16x16 knight 3.png");
                Health_Char = 100;
                Armor += 2;
        }
        Exp_Char = 0;
    }
   // std::cout << Cam.x << ' ' << Cam.y << '\n';

   TextureManager::Render(30, 580, 200, 200, MoveCharacter, NULL, 0, NULL, SDL_FLIP_NONE);
    TextureManager::Render(1100, 40, RectScore.w, RectScore.h, TexScore, NULL, 0, NULL, SDL_FLIP_NONE);
    TextureManager::Render(1100, 680, 60, 60, ButtonAttack, NULL, 0, NULL, SDL_FLIP_NONE);
   // TextureManager::Render(1100, 680, TextAttack.w, TextAttack.h, TimeCoolDownAttack, NULL, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(Game::Renderer, TimeCoolDownAttack, NULL, &TimeAttack, 0 , NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(Game::Renderer, CharTex, &Current, &srcRect, 0, NULL, Check);
    if(checkEffectRun == true) SDL_RenderCopyEx(Game::Renderer, EffectRun, &RunRect[cntEffectRun], &Allow, 0, NULL, checkFlipRun);
}

Character::~Character()
{
    SDL_DestroyTexture(CharTex);
    delete CharTex;

    SDL_DestroyTexture(TimeCoolDownAttack);
    delete TimeCoolDownAttack;
    TTF_Quit();

    SDL_DestroyTexture(HealthLeft);
    SDL_DestroyTexture(HealthRight);
    SDL_DestroyTexture(HealthCenter);
    SDL_DestroyTexture(IconHealth);

    SDL_DestroyTexture(HealthHolderCenter);
    SDL_DestroyTexture(HealthHolderLeft);
    SDL_DestroyTexture(HealthHolderRight);

    delete HealthLeft, HealthRight, HealthCenter, IconHealth, HealthHolderCenter, HealthHolderLeft, HealthHolderRight;

    SDL_DestroyTexture(ExpLeft);
    SDL_DestroyTexture(ExpRight);
    SDL_DestroyTexture(ExpCenter);
    SDL_DestroyTexture(IconExp);

    SDL_DestroyTexture(ExpHolderCenter);
    SDL_DestroyTexture(ExpHolderLeft);
    SDL_DestroyTexture(ExpHolderRight);

    delete ExpLeft, ExpRight, ExpCenter, IconExp, ExpHolderCenter, ExpHolderLeft, ExpHolderRight;

    TTF_Quit();
}
