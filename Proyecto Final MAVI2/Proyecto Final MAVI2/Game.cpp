#include "Game.h"

Game::Game() : mState(MENU), mFps(60.f), mFrameTime(1.f / mFps), mActualTime(0.f), nextLevel(false)
{

	mWindow = new RenderWindow(VideoMode(1280, 720), "GAME SFML MENU + LEVELS");
	mWindow->setFramerateLimit(mFps);  

	mContactListener = new ContactListener;

	mEvent = new Event;
	mCamara = new View;
	mClock = new Clock;
	mInitTime = new Time;

	mNextLevel = new Text("siguiente nivel", *mFont, 40);
	mNextLevel->setPosition(400, 300);
	nextLevel = false;

	SetMenu();
	SetImages();
	InitPhysics();
	CheckCollisions();
	mFloorAvatar = new Avatar(mBodyFloor, mFloorSp);
	mCanonAvatar = new Avatar(mBodyCanon, mCanonSp);
	mBox = new Box(*mWorld);
}

void Game::SetCamara(float mZoom)
{

	mCamara->setSize(mWindow->getSize().x * mZoom, mWindow->getSize().y * mZoom);
	mCamara->setCenter(20, 100);
	mWindow->setView(*mCamara);
}

void Game::SetMenu()
{
	mBackMenuTx = new Texture;
	if (!mBackMenuTx->loadFromFile("Assets/yellowBack.png")) { cout << "Error al cargar imagen de fondo en menu" << endl; }
	mBackMenuSp = new Sprite;
	mBackMenuSp->setTexture(*mBackMenuTx);
	mBackMenuSp->setScale(1280.f / mBackMenuTx->getSize().x, 720.f / mBackMenuTx->getSize().y);

	mFont = new Font;
	if (!mFont->loadFromFile("Fonts/Bodoni.ttf")) { cout << "Error al cargar la fuente" << endl; }

	mTitle = new Text("Menu Principal", *mFont, 50);
	mTitle->setPosition(270, 150);
	mPlay = new Text("Play", *mFont, 40);
	mPlay->setPosition(600, 300);
	mExit = new Text("Exit", *mFont, 40);
	mExit->setPosition(600, 400);
}

void Game::SetImages()
{

	mCrosshairTx = new Texture;
	mBackLv1Tx = new Texture;
	mFloorTx = new Texture;
	mCanonTx = new Texture;
	mCanonBaseTx = new Texture;
	
	if (!mCrosshairTx->loadFromFile("Assets/crosshair.png")) { cout << "Error al cargar la textura de crosshair" << endl; }
	if (!mBackLv1Tx->loadFromFile("Assets/blueBack.png")) { cout << "Error al cargar la textura del fondo" << endl; }
	if (!mFloorTx->loadFromFile("Assets/floor.png")) { cout << "Error al cargar la textura del piso" << endl; }
	if (!mCanonTx->loadFromFile("Assets/canonBody.png")) { cout << "Error al cargar la textura del canion" << endl; }
	if (!mCanonBaseTx->loadFromFile("Assets/canonBase.png")) { cout << "Error al cargar la textura del pie de canion" << endl; }

	mCrosshairSp = new Sprite;
	mBackLv1Sp = new Sprite;
	mFloorSp = new Sprite;
	mCanonSp = new Sprite;
	mCanonBaseSp = new Sprite;

	//Crosshair
	mCrosshairSp->setTexture(*mCrosshairTx);
	mCrosshairSp->setScale(0.10f, 0.10f);
	mCrosshairSp->setOrigin(mCrosshairTx->getSize().x / 2, mCrosshairTx->getSize().y / 2);
	mCrosshairSp->setPosition(mWindow->mapPixelToCoords(Mouse::getPosition(*mWindow)));

	//Background
	mBackLv1Sp->setTexture(*mBackLv1Tx);
	mBackLv1Sp->setScale(260.f / mBackLv1Tx->getSize().x, 150.f / mBackLv1Tx->getSize().y);
	mBackLv1Sp->setPosition({ -110.f, 25.f }); 

	//Piso
	mFloorSp->setTexture(*mFloorTx);

	//Canion y pie de canion
	mCanonSp->setTexture(*mCanonTx);
	mCanonBaseSp->setTexture(*mCanonBaseTx);
	mCanonBaseSp->setScale(50.f / mCanonBaseTx->getSize().x, 50.f / mCanonBaseTx->getSize().y);
	mCanonBaseSp->setPosition({ -121.5f, 135.f });
}

void Game::InitPhysics() 
{

	mWorld = new b2World({ 0.f, 9.8f });

	//Piso
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
	mBodyFloor->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

	//Canion
	mBodyDefCanon.type = b2_kinematicBody;
	mBodyDefCanon.position = b2Vec2(-95.f, 154.f);
	mBodyCanon = mWorld->CreateBody(&mBodyDefCanon);
	b2PolygonShape mCanonShape;
	mCanonShape.SetAsBox(20.f, 20.f);
	mFixtureDefCanon.shape = &mCanonShape;
	mFixtureDefCanon.density = 0.3f;
	mFixtureDefCanon.restitution = 0.3f;
	mFixtureDefCanon.friction = 0.3f;
	mFixtureCanon = mBodyCanon->CreateFixture(&mFixtureDefCanon);
	mBodyCanon->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

void Game::CheckCollisions()
{

	mWorld->SetContactListener(mContactListener);
}

void Game::UpdatePhysics() 
{

	mWorld->Step(mFrameTime, 8, 8);
	mWorld->ClearForces();

	// Cambiar de nivel si nextLevel es verdadero
	if (nextLevel)
	{
		mState = LEVEL2;
	}
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
				if (nextLevel)
				{
					nextLevel = false;
					mState = LEVEL2;
				}

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
					b2Vec2 mCanonTipPosition = mBodyCanon->GetWorldPoint(b2Vec2(11.f, -5.f)); // Ajusta según la longitud del cañón 
					mRagdoll = new Ragdoll({ mCanonTipPosition.x, mCanonTipPosition.y }, *mWorld); 
					mRagdoll->ApplyForce(Vector2f(mPositionMouse.x - mBodyCanon->GetPosition().x, mPositionMouse.y - mBodyCanon->GetPosition().y));
				}
			} 
		} 

		if (mEvent->type == Event::MouseMoved)
		{
			Vector2f mPositionMouse;
			mPositionMouse = mWindow->mapPixelToCoords(Mouse::getPosition(*mWindow));
			mBodyCanon->SetTransform(mBodyCanon->GetPosition(), atan2f(mPositionMouse.y - mBodyCanon->GetPosition().y, mPositionMouse.x - mBodyCanon->GetPosition().x));
		}
	} 
}

void Game::Update()
{ 

	if (mState == LEVEL1 && mClock->getElapsedTime().asSeconds() >= 500) 
	{ 
		mState = LEVEL2; 
		cout << "level2" << endl; 
		nextLevel = true;
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

void Game::RunLevel()
{

	SetCamara(0.20f);
	SetImages();

	mWindow->setMouseCursorVisible(false);
	mWindow->draw(*mBackLv1Sp);
	mWindow->draw(*mCrosshairSp);
	mFloorAvatar->Draw(*mWindow);
	mCanonAvatar->Draw(*mWindow);
	mWindow->draw(*mCanonBaseSp);
	mBox->Draw(*mWindow);

	if (mRagdoll != nullptr)
	{
		mRagdoll->Draw(*mWindow);
	}
}

void Game::RunLevel2() {}
void Game::RunLevel3() {}

void Game::DrawMenu() 
{ 

	mWindow->draw(*mBackMenuSp);
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
	    RunLevel(); 
		if (nextLevel)
		{
			mWindow->draw(*mNextLevel);
		}
	    break; 
	case LEVEL2: 
	    RunLevel2(); 
	    break; 
	case LEVEL3: 
	    RunLevel3(); 
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
	delete mNextLevel;
	delete mClock;
	delete mInitTime;
	delete mCamara;
	delete mEvent;
	delete mBackLv1Sp;
	delete mFloorSp;
	delete mCanonSp;
	delete mCanonBaseSp;
	delete mCrosshairSp;
	delete mBackMenuSp;

	mWorld->DestroyBody(mBodyFloor);
	mWorld->DestroyBody(mBodyCanon);
}