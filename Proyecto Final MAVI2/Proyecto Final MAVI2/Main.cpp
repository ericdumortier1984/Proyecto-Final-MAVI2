#include "MainMenu.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

int main()
{

	RenderWindow MENU(VideoMode(1280, 720), "PROYECTO FINAL MAVI2");
	MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);

	while (MENU.isOpen())
	{
		Event event;
		while (MENU.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				MENU.close();
			}
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
				if (event.key.code == Keyboard::Enter)
				{
					int x = mainMenu.MainMenuPressed();
					if (x == 0)
					{
						MENU.clear();
						Level1* Go;
						Go = new Level1(MENU.getSize().x, MENU.getSize().y);
						Go->Run();
						MENU.display();
					}
					if (x == 1)
					{
						MENU.clear();
						Level2* Go;
						Go = new Level2(MENU.getSize().x, MENU.getSize().y);
						Go->Run();
						MENU.display();
					}
					if (x == 2)
					{
						MENU.clear();
						Level3* Go;
						Go = new Level3(MENU.getSize().x, MENU.getSize().y);
						Go->Run();
						MENU.display();
					}
					if (x == 3)
					{
						MENU.clear();
						// Aqui va a ir la class INFO
						MENU.display();
					}
					if (x == 4)
					{
						MENU.close();
						break;
					}
				}
			}
			MENU.clear();
			mainMenu.Draw(MENU);
			MENU.display();
		}
	}

	return EXIT_SUCCESS;
}