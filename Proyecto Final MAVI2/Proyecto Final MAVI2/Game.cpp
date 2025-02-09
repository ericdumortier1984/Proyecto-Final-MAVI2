#include "Game.h"

// Constructor
Game::Game() :mWindow(VideoMode(1280, 720), "PROYECTO FINAL MAVI2"), mainMenu(mWindow.getSize().x, mWindow.getSize().y),inLevelMenu(false),inInfoMenu(false)
{

}

// Metodo para ejecutar el juego
void Game::Run()
{
    while (mWindow.isOpen())
    {
        ProcessEvents();
        Render();
    }
}

// metodo para procesar eventos de la ventana
void Game::ProcessEvents()
{
    Event event;
    while (mWindow.pollEvent(event))
    {
        // Cerrar ventana
        if (event.type == Event::Closed)
        {
            mWindow.close();
        }

        // Eventos de teclado UP AND DOWN
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Up)
            {
                mainMenu.MoveUp();
                break;
            }
            if (event.key.code == Keyboard::Down)
            {
                mainMenu.MoveDown();
                break;
            }

            //Eventos de teclado ESCAPE
            if (event.key.code == Keyboard::Escape)
            {
                if (inLevelMenu || inInfoMenu)
                {
                    mainMenu.PlayMusic();
                    inLevelMenu = false;
                    inInfoMenu = false;
                }
                else
                {
                    mainMenu.StopMusic();
                    mWindow.close();
                }
                break;
            }

            // Eventos de teclado ENTER
            if (event.key.code == Keyboard::Enter)
            {
                int x = mainMenu.MainMenuPressed();
                if (x == 0)
                {
                    inLevelMenu = true;
                }
                if (x == 1)
                {
                    inInfoMenu = true;
                }
                if (x == 2)
                {
                    mWindow.close();
                    break;
                }
            }
        }

        // Eventos de MOUSE
        if (event.type == Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == Mouse::Left)
            {
                Vector2f mousePos = mWindow.mapPixelToCoords(Mouse::getPosition(mWindow));
                if (inLevelMenu)
                {
                    mainMenu.MouseMove(mousePos);
                    int x = mainMenu.LevelMenuPressed();
                    if (x != -1)
                    {
                        if (x == 0)
                        {
                            mWindow.clear();
                            Level1* Go;
                            Go = new Level1(mWindow.getSize().x, mWindow.getSize().y, true);
                            Go->Run();
                            mWindow.display();
                        }
                        if (x == 1)
                        {
                            mWindow.clear();
                            Level2* Go;
                            Go = new Level2(mWindow.getSize().x, mWindow.getSize().y, true);
                            Go->Run();
                            mWindow.display();
                        }
                        if (x == 2)
                        {
                            mWindow.clear();
                            Level3* Go;
                            Go = new Level3(mWindow.getSize().x, mWindow.getSize().y, true);
                            Go->Run();
                            mWindow.display();
                        }
                        inLevelMenu = false;
                    }
                }
            }
        }
    }
}

// Metodo para renderizar el contenido de la ventana
void Game::Render()
{
    mWindow.clear();
    if (inLevelMenu)
    {
        mainMenu.DrawLevelMenu(mWindow);
    }
    else if (inInfoMenu)
    {
        mainMenu.DrawInfo(mWindow);
    }
    else
    {
        mainMenu.Draw(mWindow);
    }
    mWindow.display();
}