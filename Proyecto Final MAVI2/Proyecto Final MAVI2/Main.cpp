#include<box2d/box2d.h>
#include<SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

enum GameState { MENU, LEVEL1, LEVEL2, LEVEL3, EXIT };

void RunLevel1(RenderWindow& window) 
{

	CircleShape player(50);
	player.setFillColor(Color::Cyan);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == Event::Closed) 
			{
				window.close();
			}
			// Logica
		}

		window.clear();
		window.draw(player);
		window.display();
	}
};

void RunLevel2(RenderWindow& window) 
{

	RectangleShape player(Vector2f(50.f, 50.f));
	player.setFillColor(Color::Magenta);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			// Logica
		}

		window.clear();
		window.draw(player);
		window.display();
	}
};
void RunLevel3(RenderWindow& window) 
{
	
	CircleShape player(50);
	player.setFillColor(Color::Yellow);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			// Logica
		}

		window.clear();
		window.draw(player);
		window.display();
	}
};

int main(int argc, char* argv[])
{

	RenderWindow window(VideoMode(800, 600), "GAME SFML MENU + LEVELS");
	GameState state = MENU;

	// Cargar fuentes y texturas para el menu
	Font font;
	if (!font.loadFromFile("Fonts/Bodoni.ttf"))
	{
		cout << "Error al cargar la fuente" << endl;
		return -1;
	}

	Text title("Menu Principal", font, 50);
	title.setPosition(20, 150);

	Text play("Play", font, 30);
	play.setPosition(350, 300);

	Text exit("Exit", font, 30);
	exit.setPosition(350, 400);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					if (play.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						state = LEVEL1;
					}
					if (exit.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						state = EXIT;
					}
				}
			}
		}

		window.clear();

		if (state == MENU)
		{
			window.draw(title);
			window.draw(play);
			window.draw(exit);
		}
		else if (state == LEVEL1)
		{
			RunLevel1(window);
		}
		else if (state == LEVEL2)
		{
			RunLevel2(window);
		}
		else if (state == LEVEL3)
		{
			RunLevel3(window);
		}
		else if (state == EXIT)
		{
			window.close();
		}

		window.display();
	}

	return 0;
}