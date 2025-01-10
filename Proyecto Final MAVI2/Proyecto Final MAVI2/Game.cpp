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

	SetImages();
	InitPhysics();
	floorAvatar = new Avatar(mBodyFloor, mFloorSp);
}

void Game::SetCamara(float mZoom)
{

	mCamara->setSize(mWindow->getSize().x * mZoom, mWindow->getSize().y * mZoom);
	mCamara->setCenter(mWindow->getSize().x / 2, mWindow->getSize().y / 2);
	mWindow->setView(*mCamara);
}

void Game::SetImages()
{

	mFloorTx = new Texture;
	mBackLv1Tx = new Texture;
	mBackLv2Tx = new Texture;
	mBackLv3Tx = new Texture;

	mFloorTx->loadFromFile("Assets/floor.png");
	mBackLv1Tx->loadFromFile("Assets/blueBack.png");

	mFloorSp = new Sprite;
	mBackLv1Sp = new Sprite;
	mBackLv2Sp = new Sprite;
	mBackLv3Sp = new Sprite;

	mFloorSp->setTexture(*mFloorTx);
	mBackLv1Sp->setTexture(*mBackLv1Tx);

	mBackLv1Sp->setScale(100.f / mBackLv1Tx->getSize().x, 100.f / mBackLv1Tx->getSize().y);

	mCanonSFML = new RectangleShape;
	mCanonSFML->setFillColor(Color::White);
	mCanonSFML->setSize({5.0f, 10.0f});
	mCanonSFML->setPosition({520.f, 420.f});

}

void Game::InitPhysics() 
{

	mWorld = new b2World({ 0.f, 9.8f });

	mBodyDefFloor.type = b2_staticBody;
	mBodyDefFloor.position = b2Vec2(20.f, 100.f);
	mBodyFloor = mWorld->CreateBody(&mBodyDefFloor);
	b2PolygonShape mFloorShape;
	mFloorShape.SetAsBox(90.f, 5.f);
	mFixtureDefFloor.shape = &mFloorShape;
	mFixtureDefFloor.density = 1.f;
	mFixtureDefFloor.restitution = 0.3f;
	mFixtureDefFloor.friction = 0.3f;
	mFixtureFloor = mBodyFloor->CreateFixture(&mFixtureDefFloor);
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

	SetCamara(0.20f);
	SetImages();

	CircleShape player(1);
	player.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2);
	player.setFillColor(color);

	mWindow->draw(*mBackLv1Sp);
	floorAvatar->Draw(*mWindow);
	mWindow->draw(player);
	mWindow->draw(*mCanonSFML);

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
	delete mBackLv1Sp;
	delete mFloorSp;

	mWorld->DestroyBody(mBodyFloor);
}