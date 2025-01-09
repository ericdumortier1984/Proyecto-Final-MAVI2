#include "Game.h"

Game::Game() : mState(MENU)
{

	mFps = 60.f;
	mFrameTime = 1 / mFps;
	mActualTime = 0;

	mWindow = new RenderWindow(VideoMode(1280, 720), "GAME SFML MENU + LEVELS");
	mWindow->setFramerateLimit(mFps);

	mEvent = new Event;
	mCamara = new View;
	mClock = new Clock();
	mInitTime = new Time;

	SetCamara();
	InitPhysics();

	mFont = new Font;
	if (!mFont->loadFromFile("Fonts/Bodoni.ttf")) 
	{
		std::cout << "Error al cargar la fuente" << std::endl; 
	}

	mTitle = new Text("Menu Principal", *mFont, 50);
	mTitle->setPosition(270, 150); 
	mPlay = new Text("Play", *mFont, 30); 
	mPlay->setPosition(600, 300); 
	mExit = new Text("Exit", *mFont, 30); 
	mExit->setPosition(600, 400);
}

void Game::SetCamara()
{

	mCamara->setSize(mWindow->getSize().x, mWindow->getSize().y);
	mCamara->setCenter(mWindow->getSize().x / 2, mWindow->getSize().y / 2);
	mWindow->setView(*mCamara);
}

void Game::InitPhysics() 
{

	mWorld = new b2World({ 0.f, 9.8f });
}

void Game::UpdatePhysics() 
{

	mWorld->Step(mFrameTime, 8, 8);
	mWorld->ClearForces();
}

void Game::Run() 
{ 

	while (mWindow->isOpen()) 
	{ 
		*mInitTime = mClock->getElapsedTime();

		if (mActualTime + mFrameTime < mInitTime->asSeconds())
		{
			mActualTime = mInitTime->asSeconds();
			ProcessEvents();
			Update();
			UpdatePhysics();
			Draw();
		}
	} 
}

void Game::ProcessEvents() 
{ 
 
	while (mWindow->pollEvent(*mEvent)) 
	{ 
		if (mEvent->type == Event::Closed) 
		{ 
			mWindow->close(); 
		} 
		if (mEvent->type == Event::MouseButtonPressed) 
		{ 
			if (mEvent->mouseButton.button == Mouse::Left)
			{ 
				if (mState == MENU) 
				{ 
					if (mPlay->getGlobalBounds().contains(mEvent->mouseButton.x, mEvent->mouseButton.y)) 
					{ 
						mState = LEVEL1; 
						cout << "level1" << endl; 
						mClock->restart(); 
					} 
					if (mExit->getGlobalBounds().contains(mEvent->mouseButton.x, mEvent->mouseButton.y)) 
					{
						mState = EXIT; 
					}
				} 
			} 
			else if (mEvent->mouseButton.button == Mouse::Right)
			{
				Vector2f mPositionMouse;
				mPositionMouse = mWindow->mapPixelToCoords(Mouse::getPosition(*mWindow));

				//bodyCanion->SetTransform(bodyCanion->GetPosition(),
					//atan2f(mPositionMouse.y - bodyCanion->GetPosition().y, mPositionMouse.x - bodyCanion->GetPosition().x));

				mRagdoll = new Ragdoll({ mPositionMouse.x, mPositionMouse.y }, *mWorld);
				//mRagdoll->ApplyForce(Vector2f(mPositionMouse.x - bodyCanion->GetPosition().x
					//, mPositionMouse.y - bodyCanion->GetPosition().y));
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

	if (mRagdoll != nullptr)
	{
		mRagdoll->Draw(*mWindow);
	}
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
	delete mInitTime;
	delete mCamara;
	delete mEvent;
}