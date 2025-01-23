#include "Game.h"

Game::Game() : mState(MENU), mFps(60.f), mFrameTime(1.f / mFps), mActualTime(0.f), nextLevel(false), lostLevel(false)
{

	mWindow = new RenderWindow(VideoMode(1280, 720), "PROYECTO FINAL BOX2D");
	mWindow->setFramerateLimit(mFps);  

	mContactListener = new ContactListener(this); // Pasamos la instancia del juego

	mEvent = new Event;
	mCamara = new View;
	mClock = new Clock;
	mInitTime = new Time;

	mFont = new Font;
	if (!mFont->loadFromFile("Fonts/ARLRDBD.ttf")) { cout << "Error al cargar la fuente" << endl; }

	mCountdownTimer = new Text("", *mFont, 18);	
	mCountdownTimer->setPosition(-10.f, 25.f);
	mCountdownTimer->setFillColor(Color::Yellow);
	mCountdownTimer->setOutlineThickness(2);
	mCountdownTimer->setOutlineColor(Color::Black);
	// cout << "[CRONOMETRO]" << endl; //Debug

	mNextLevel = new Text("NEXT LEVEL: CLICK TO START", *mFont, 80);
	mNextLevel->setPosition(mWindow->getSize().x / 2.f, mWindow->getSize().y / 2.f);

	SetMenu();
	SetImages();
	InitPhysics();
	CheckCollisions();

	mCanon = new Canon(*mWorld);
	mFloor = new Floor(*mWorld);
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
	if (!mBackMenuTx->loadFromFile("Assets/Backgrounds/backgroundMain2.jpg")) { cout << "Error al cargar imagen de fondo en menu" << endl; }
	mBackMenuSp = new Sprite;
	mBackMenuSp->setTexture(*mBackMenuTx);
	mBackMenuSp->setScale(1280.f / mBackMenuTx->getSize().x, 720.f / mBackMenuTx->getSize().y);

	mButtonPlayTx = new Texture;
	if (!mButtonPlayTx->loadFromFile("Assets/Backgrounds/playButton.png")) { cout << "Error al cargar imagen de boton play" << endl; }
	mButtonPlaySp = new Sprite;
	mButtonPlaySp->setTexture(*mButtonPlayTx);
	mButtonPlaySp->setScale(0.20f, 0.20f);
	mButtonPlaySp->setPosition(580.f, 380.f);

	mPlayText = new Text;
	mPlayText->setFont(*mFont);
	mPlayText->setFillColor(Color::White);
	mPlayText->setOutlineColor(Color::Black);
	mPlayText->setOutlineThickness(5.f);
	mPlayText->setCharacterSize(40);
	mPlayText->setPosition(260.f, 420.f);
	mPlayText->setString("PLAY BUTTON --");

	mButtonExitTx = new Texture;
	if (!mButtonExitTx->loadFromFile("Assets/Backgrounds/exitButton.png")) { cout << "Error al cargar imagen de boton exit" << endl; }
	mButtonExitSp = new Sprite;
	mButtonExitSp->setTexture(*mButtonExitTx);
	mButtonExitSp->setScale(0.25f, 0.25f);
	mButtonExitSp->setPosition(580.f, 550.f);

	mExitText = new Text;
	mExitText->setFont(*mFont);
	mExitText->setFillColor(Color::White);
	mExitText->setOutlineColor(Color::Black);
	mExitText->setOutlineThickness(5.f);
	mExitText->setCharacterSize(40);
	mExitText->setPosition(270.f, 580.f);
	mExitText->setString("EXIT BUTTON --");

	mTitleTx = new Texture;
	if (!mTitleTx->loadFromFile("Assets/Backgrounds/title.png")) { cout << "Error al cargar imagen de titulo" << endl; }
	mTitleSp = new Sprite;
	mTitleSp->setTexture(*mTitleTx);
	mTitleSp->setScale(1.25f, 0.75f);
	mTitleSp->setPosition(200.f, 0.f);
}

void Game::SetImages()
{

	mCrosshairTx = new Texture;
	mBackLv1Tx = new Texture;
	
	if (!mCrosshairTx->loadFromFile("Assets/Objects/crosshair.png")) { cout << "Error al cargar la textura de crosshair" << endl; }
	if (!mBackLv1Tx->loadFromFile("Assets/Backgrounds/blueBack.png")) { cout << "Error al cargar la textura del fondo" << endl; }

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
				if (mState == MENU)
				{
					if (mButtonPlaySp->getGlobalBounds().contains(mEvent->mouseButton.x, mEvent->mouseButton.y))
					{
						mState = LEVEL1;
						cout << "[LEVEL 1]" << endl;
						mClock->restart();
					}
					else if (mButtonExitSp->getGlobalBounds().contains(mEvent->mouseButton.x, mEvent->mouseButton.y))
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

	float timeRemaining = 0.f;

	if (mState == LEVEL1)
	{ 
		timeRemaining = LEVEL1_TIME_LIMIT - mClock->getElapsedTime().asSeconds();
		//cout << "[TIME REMAINING: ]" << timeRemaining << endl; // Debug
		if (timeRemaining <= 0)
		{
			// cout << "[TIME UP LEVEL 1]" << endl; // Debug
			mState = EXIT;
		}
	} 
	else if (mState == LEVEL2 && mClock->getElapsedTime().asSeconds() >= LEVEL2_TIME_LIMIT) 
	{
		cout << "[TIME UP LEVEL 2]" << endl;
		mState = EXIT;
	} 

	int seconds = static_cast<int>(timeRemaining) % 180;
	mCountdownTimer->setString("TIME: " + to_string(seconds));

	if (nextLevel) // Si se ha solicitado el próximo nivel
	{
		cout << "[CHANGE TO NEXT LEVEL]" << endl;
		NextLevel(); // Cambiar el estado del nivel.
		nextLevel = false; // Reinicia la variable.
		mClock->restart(); // Reiniciar el tiempo para el nuevo nivel.
	}
}

void Game::RunLevel1()
{

	SetCamara(0.20f);
	SetImages();

	mWindow->setMouseCursorVisible(false);
	mWindow->draw(*mBackLv1Sp);
	mWindow->draw(*mCountdownTimer);
	mWindow->draw(*mCrosshairSp);
	mFloor->Draw(*mWindow);
	mCanon->Draw(*mWindow);
	for (int i = 0; i < 5; ++i) { if (mBox[i] != nullptr) mBox[i]->Draw(*mWindow); }
	if (mCircleOfFire != nullptr) { mCircleOfFire->Draw(*mWindow); }
	if (mRagdoll != nullptr) { mRagdoll->Draw(*mWindow); }
}

void Game::RunLevel2() 
{

	SetCamara(0.20f);
	SetImages();

	mWindow->setMouseCursorVisible(false);
	mWindow->draw(*mBackLv1Sp);
	mWindow->draw(*mCrosshairSp);
	mFloor->Draw(*mWindow);
	mCanon->Draw(*mWindow);
	if (mRagdoll != nullptr) { mRagdoll->Draw(*mWindow); }
}

void Game::DrawMenu() 
{ 

	mWindow->draw(*mBackMenuSp);
	mWindow->draw(*mTitleSp);
	mWindow->draw(*mButtonPlaySp);
	mWindow->draw(*mButtonExitSp);
	mWindow->draw(*mPlayText);
	mWindow->draw(*mExitText);
	//cout << "[MAIN MENU]" << endl; // Debug
}

bool Game::NextLevel()
{

	if (mState == LEVEL1)
	{
		mState = LEVEL2;
	}
	else if (mState == LEVEL2)
	{
		mState = EXIT;
		cout << "[EXIT GAME]" << endl;
	}

	return nextLevel;
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
		if (mBox[0] == nullptr) mBox[0] = new Box(*mWorld, { 70.f, 100.5f });
		if (mBox[1] == nullptr) mBox[1] = new Box(*mWorld, { 70.f, 110.5f });
		if (mBox[2] == nullptr) mBox[2] = new Box(*mWorld, { 70.f, 120.5f });
		if (mBox[3] == nullptr) mBox[3] = new Box(*mWorld, { 70.f, 130.5f });
		if (mBox[4] == nullptr) mBox[4] = new Box(*mWorld, { 70.f, 140.5f });
		if (mCircleOfFire == nullptr) mCircleOfFire = new CircleOfFire(*mWorld, { 120.f, 140.5f });
	    RunLevel1(); 
		if (nextLevel)
		{
			mWindow->draw(*mNextLevel);
		}
	    break; 
	case LEVEL2: 
		if (mBox == nullptr) mBox[0] = new Box(*mWorld, { 110.f, 140.5f });
	    RunLevel2();
		if (nextLevel)
		{
			mWindow->draw(*mNextLevel);
		}
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
	delete mTitleTx;
	delete mTitleSp;
	delete mButtonPlayTx;
	delete mButtonPlaySp;
	delete mButtonExitTx;
	delete mButtonExitSp;
	delete mPlayText;
	delete mExitText;
	delete mNextLevel;
	delete mClock;
	delete mInitTime;
	delete mCamara;
	delete mEvent;
	delete mBackLv1Sp;
	delete mCrosshairSp;
	delete mBackMenuSp;
	delete mCountdownTimer;
}