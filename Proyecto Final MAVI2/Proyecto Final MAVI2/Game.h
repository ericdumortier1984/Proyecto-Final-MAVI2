#pragma once
#include "MainMenu.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

class Game
{
public:

    Game();
    void Run();

private:

    RenderWindow mWindow;
    MainMenu mainMenu;
    bool inLevelMenu;
    bool inInfoMenu;

    void ProcessEvents();
    void Render();
};