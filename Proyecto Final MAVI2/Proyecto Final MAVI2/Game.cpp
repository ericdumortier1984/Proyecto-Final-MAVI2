#include "Game.h"

Game::Game() : mState(MENU), mFps(60.f), mFrameTime(1.f / mFps), mActualTime(0.f), nextLevel(false), winLevel(false), lostLevel(false)
{

	mWindow = new RenderWindow(VideoMode(1280, 720), "GAME SFML MENU + LEVELS");
	mWindow->setFramerateLimit(mFps);  

	mContactListener = new ContactListener(this); // Pasamos la instancia del juego

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
	mFloor = new Floor(*mWorld);
	mCanon = new Canon(*mWorld);
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
	
	if (!mCrosshairTx->loadFromFile("Assets/crosshair.png")) { cout << "Error al cargar la textura de crosshair" << endl; }
	if (!mBackLv1Tx->loadFromFile("Assets/blueBack.png")) { cout << "Error al cargar la textura del fondo" << endl; }

	mCrosshairSp = new Sprite;
	mBackLv1Sp = new Sprite;

	//Crosshair
	mCrosshairSp->setTexture(*mCrosshairTx);
	mCrosshairSp->setScale(0.10f, 0.10f);
	mCrosshairSp->setOrigin(mCrosshairTx->getSize().x / 2, mCrosshairTx->getSize().y / 2);
	mCrosshairSp->setPosition(mWindow->mapPixelToCoords(Mouse::getPosition(*mWindow)));

	//Background
	mBackLv1Sp->setTexture(*mBackLv1Tx);
	mBackLv1Sp->setScale(260.f / mBackLv1Tx->getSize().x, 150.f / mBackLv1Tx->getSize().y);
	mBackLv1Sp->setPosition({ -110.f, 25.f }); 
}

void Game::InitPhysics() 
{

	mWorld = new b2World({ 0.f, 9.8f });
}

void Game::CheckCollisions()
{

	mWorld->SetContactListener(mContactListener);
}

void Game::CheckWin()
{

	//if (mRagdoll->CheckCollision() && mBox->CheckCollision())
	//{
		//cout << "Nivel superado" << endl;
		//winLevel = true;
	//}
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
			CheckCollisions();
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
					mCanon->Shoot(mWorld, mPositionMouse, *mWindow);
					mRagdoll = mCanon->GetRagdoll();
				}
			} 
		} 

		if (mEvent->type == Event::MouseMoved)
		{
			Vector2f mPositionMouse;
			mPositionMouse = mWindow->mapPixelToCoords(Mouse::getPosition(*mWindow));
			mCanon->Update(mPositionMouse);
		}
	} 
}

void Game::Update()
{ 

	if (mState == LEVEL1 && mClock->getElapsedTime().asSeconds() >= LEVEL1_TIME_LIMIT) 
	{ 
		cout << "Time up" << endl;
		mState = EXIT;
		//mState = LEVEL2; 
		//cout << "level2" << endl; 
		//nextLevel = true;
		//mClock->restart(); 
	} 
	else if (mState == LEVEL2 && mClock->getElapsedTime().asSeconds() >= LEVEL2_TIME_LIMIT) 
	{
		cout << "Time up" << endl;
		mState = EXIT;
		//mState = LEVEL3; 
		//cout << "level3" << endl; 
		//mClock->restart();
	} 
	else if (mState == LEVEL3 && mClock->getElapsedTime().asSeconds() >= LEVEL3_TIME_LIMIT) 
	{ 
		cout << "Time Up" << endl;
		mState = EXIT; 
	} 
}

void Game::RunLevel()
{

	SetCamara(0.20f);
	SetImages();

	mWindow->setMouseCursorVisible(false);
	mWindow->draw(*mBackLv1Sp);
	mWindow->draw(*mCrosshairSp);
	mFloor->Draw(*mWindow);
	mCanon->Draw(*mWindow);
	mBox->Draw(*mWindow);

	if (mRagdoll != nullptr)
	{
		mRagdoll->Draw(*mWindow);
	}

	CheckWin();

	//mRagdoll->VerWin();
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

bool Game::NextLevel()
{

	return nextLevel = true;
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
	delete mCrosshairSp;
	delete mBackMenuSp;

}