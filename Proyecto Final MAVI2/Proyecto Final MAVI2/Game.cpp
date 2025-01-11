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
	canonAvatar = new Avatar(mBodyCanon, mCanonSp);
}

void Game::SetCamara(float mZoom)
{

	mCamara->setSize(mWindow->getSize().x * mZoom, mWindow->getSize().y * mZoom);
	mCamara->setCenter(20, 100);
	mWindow->setView(*mCamara);
}

void Game::SetImages()
{

	mBackLv1Tx = new Texture;
	mFloorTx = new Texture;
	mCanonTx = new Texture;
	
	if (!mBackLv1Tx->loadFromFile("Assets/blueBack.png"))
	{
		cout << "Error al cargar la textura del fondo" << endl;
	}
	if (!mFloorTx->loadFromFile("Assets/floor.png"))
	{
		cout << "Error al cargar la textura del piso" << endl;
	}
	if (!mCanonTx->loadFromFile("Assets/canon.png"))
	{
		cout << "Error al cargar la textura del canion" << endl;
	}

	mBackLv1Sp = new Sprite;
	mFloorSp = new Sprite;
	mCanonSp = new Sprite;

	mBackLv1Sp->setTexture(*mBackLv1Tx);
	mBackLv1Sp->setScale(260.f / mBackLv1Tx->getSize().x, 150.f / mBackLv1Tx->getSize().y);
	mBackLv1Sp->setPosition({ -110.f, 25.f }); 

	mFloorSp->setTexture(*mFloorTx);
    mFloorSp->setScale({ 1.f, 1.f });

	mCanonSp->setTexture(*mCanonTx);
	mCanonSp->setScale({ 1.f, 1.f });
}

void Game::InitPhysics() 
{

	mWorld = new b2World({ 0.f, 9.8f });

	//floor
	mBodyDefFloor.type = b2_staticBody;
	mBodyDefFloor.position = b2Vec2(0.f, 170.f);
	mBodyFloor = mWorld->CreateBody(&mBodyDefFloor);
	b2PolygonShape mFloorShape;
	mFloorShape.SetAsBox(190.f, 5.f);
	mFixtureDefFloor.shape = &mFloorShape;
	mFixtureDefFloor.density = 1.f;
	mFixtureDefFloor.restitution = 0.3f;
	mFixtureDefFloor.friction = 0.3f;
	mFixtureFloor = mBodyFloor->CreateFixture(&mFixtureDefFloor);

	//canon
	mBodyDefCanon.type = b2_kinematicBody;
	mBodyDefCanon.position = b2Vec2(-95.f, 160.f);
	mBodyCanon = mWorld->CreateBody(&mBodyDefCanon);
	b2PolygonShape mCanonShape;
	mCanonShape.SetAsBox(5.f, 5.f);
	mFixtureDefCanon.shape = &mCanonShape;
	mFixtureDefCanon.density = 0.3f;
	mFixtureDefCanon.restitution = 0.3f;
	mFixtureDefCanon.friction = 0.3f;
	mFixtureCanon = mBodyCanon->CreateFixture(&mFixtureDefCanon);

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
					else if (mExit->getGlobalBounds().contains(mEvent->mouseButton.x, mEvent->mouseButton.y)) 
					{
						mState = EXIT; 
					}
				} 
				else
				{
					Vector2f mPositionMouse;
					mPositionMouse = mWindow->mapPixelToCoords(Mouse::getPosition(*mWindow));
					b2Vec2 mCanonTipPosition = mBodyCanon->GetWorldPoint(b2Vec2(5.f, 0.f)); // Ajusta 5.f según la longitud del cañón 
					mRagdoll = new Ragdoll({ mCanonTipPosition.x, mCanonTipPosition.y }, *mWorld); 
					mRagdoll->ApplyForce(Vector2f(mPositionMouse.x - mBodyCanon->GetPosition().x, mPositionMouse.y - mBodyCanon->GetPosition().y));
				}
			} 
		} 

		if (mEvent->type == Event::MouseMoved)
		{
			Vector2f mPositionMouse;
			mPositionMouse = mWindow->mapPixelToCoords(Mouse::getPosition(*mWindow));
			mBodyCanon->SetTransform(mBodyCanon->GetPosition(),atan2f(mPositionMouse.y - mBodyCanon->GetPosition().y, mPositionMouse.x - mBodyCanon->GetPosition().x));
		}
	} 
}

void Game::Update()
{ 

	if (mState == LEVEL1 && mClock->getElapsedTime().asSeconds() >= 1000) 
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
	canonAvatar->Draw(*mWindow);
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
	delete mBackLv1Sp;
	delete mFloorSp;
	delete mCanonSp;

	mWorld->DestroyBody(mBodyFloor);
}