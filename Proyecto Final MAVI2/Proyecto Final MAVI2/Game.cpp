#include "Game.h"

Game::Game() : mState(MENU)
{

	mWindow = new RenderWindow(VideoMode(800, 600), "GAME SFML MENU + LEVELS");
	mWindow->setFramerateLimit(60);

	mFont = new Font;
	if (!mFont->loadFromFile("Fonts/Bodoni.ttf")) 
	{
		std::cout << "Error al cargar la fuente" << std::endl; // Manejar error 
	}

	mTitle = new Text("Menu Principal", *mFont, 50);
	mTitle->setPosition(20, 150); 
	mPlay = new Text("Play", *mFont, 30); 
	mPlay->setPosition(350, 300); 
	mExit = new Text("Exit", *mFont, 30); 
	mExit->setPosition(350, 400);

	mClock = new Clock();
}

void Game::Run() 
{ 

	while (mWindow->isOpen()) 
	{ 
		ProcessEvents();
		Update();
		Draw();
	} 
}

void Game::ProcessEvents() 
{ 

	Event event; 
	while (mWindow->pollEvent(event)) 
	{ 
		if (event.type == Event::Closed) 
		{ 
			mWindow->close(); 
		} 
		if (event.type == Event::MouseButtonPressed) 
		{ 
			if (event.mouseButton.button == Mouse::Left)
			{ 
				if (mState == MENU) 
				{ 
					if (mPlay->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) 
					{ 
						mState = LEVEL1; 
						cout << "level1" << endl; 
						mClock->restart(); 
					} 
					if (mExit->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) 
					{
						mState = EXIT; 
					}
				} 
			} 
		} 
	} 
}

void Game::Update()
{ 

	if (mState == LEVEL1 && mClock->getElapsedTime().asSeconds() >= 10) 
	{ 
		mState = LEVEL2; 
		cout << "level2" << endl; 
		mClock->restart(); 
	} 
	else if (mState == LEVEL2 && mClock->getElapsedTime().asSeconds() >= 10) 
	{
		mState = LEVEL3; 
		cout << "level3" << endl; 
		mClock->restart();
	} 
	else if (mState == LEVEL3 && mClock->getElapsedTime().asSeconds() >= 10) 
	{ 
		mState = EXIT;
		cout << "finish" << endl; 
	} 
}

void Game::RunLevel(Color color)
{

	CircleShape player(50);
	player.setFillColor(color);
	mWindow->draw(player);
}

void Game::DrawMenu() 
{ 

	mWindow->draw(*mTitle);
	mWindow->draw(*mPlay); 
	mWindow->draw(*mExit); 
}

void Game::Draw() 
{ 
	mWindow->clear(); 

	switch (mState) 
	{ 
	case MENU: 
	    DrawMenu();
	    break; 
	case LEVEL1: 
	    RunLevel(Color::Cyan); 
	    break; 
	case LEVEL2: 
	    RunLevel(Color::Magenta); 
	    break; 
	case LEVEL3: 
	    RunLevel(Color::Yellow); 
	    break; 
	case EXIT:
		mWindow->close(); 
	    break; 
	}

	mWindow->display();
}

Game::~Game()
{

	delete mWindow;
	delete mFont;
	delete mTitle;
	delete mPlay;
	delete mExit;
	delete mClock;
}