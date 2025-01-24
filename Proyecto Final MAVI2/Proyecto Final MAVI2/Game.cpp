#include "Game.h"

Game::Game() : mState(MENU), mFps(60.f), mFrameTime(1.f / mFps), mActualTime(0.f), nextLevel(false)
{

	mWindow = new RenderWindow(VideoMode(1280, 720), "PROYECTO FINAL BOX2D");
	mWindow->setFramerateLimit(mFps);  

	mContactListener = new ContactListener(this);
	mUI = new UI;

	mEvent = new Event;
	mCamara = new View;
	mClock = new Clock;
	mInitTime = new Time;

	mFont = new Font;
	if (!mFont->loadFromFile("Fonts/ARLRDBD.ttf")) { cout << "Error al cargar la fuente" << endl; }

	mCountdownTimer = new Text;	
	mCountdownTimer->setFont(*mFont);
	mCountdownTimer->setCharacterSize(12);
	mCountdownTimer->setPosition(-5.f, 28.f);
	mCountdownTimer->setFillColor(Color::White);
	mCountdownTimer->setOutlineThickness(1);
	mCountdownTimer->setOutlineColor(Color::Black);
	cout << "[CRONOMETRO]" << endl; //Debug

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
					if (mUI->IsPlayButtonClicked(mEvent->mouseButton.x, mEvent->mouseButton.y))
					{
						mState = LEVEL1;
						//mState = NEWMENU;
						cout << "[LEVEL 1]" << endl;
						mClock->restart();
					}
					else if (mUI->IsExitButtonClicked(mEvent->mouseButton.x, mEvent->mouseButton.y))
					{
						mState = EXIT;
					}
				}
				if (mState == NEWMENU)
				{
					if (mUI->IsNextLevelButtonClicked(mEvent->mouseButton.x, mEvent->mouseButton.y))
					{
						mState = LEVEL2;
						cout << "[LEVEL 2]" << endl;
						mClock->restart();
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
			cout << "[TIME UP LEVEL 1]" << endl; // Debug
			mState = EXIT;
		}
	} 
	else if (mState == LEVEL2 && mClock->getElapsedTime().asSeconds() >= LEVEL2_TIME_LIMIT) 
	{
		if (timeRemaining <= 0)
		{
			cout << "[TIME UP LEVEL 2]" << endl; // Debug
			mState = EXIT;
		}
	} 

	int seconds = static_cast<int>(timeRemaining) % 34;
	mCountdownTimer->setString("TIME: " + to_string(seconds));
}

void Game::RunLevel1()
{

	SetCamara(0.20f);
	mWindow->setMouseCursorVisible(false);
	mUI->SetImages(*mWindow);

	mUI->DrawImages(*mWindow);
	mWindow->draw(*mCountdownTimer);
	mFloor->Draw(*mWindow);
	mCanon->Draw(*mWindow);
	for (int i = 0; i < 5; ++i) { if (mBox[i] != nullptr) mBox[i]->Draw(*mWindow); }
	if (mCircleOfFire != nullptr) { mCircleOfFire->Draw(*mWindow); }
	if (mRagdoll != nullptr) { mRagdoll->Draw(*mWindow); }
}

void Game::RunLevel2() 
{

	SetCamara(0.20f);
	mWindow->setMouseCursorVisible(false);
	mUI->SetImages(*mWindow);

	mUI->DrawImages(*mWindow);
	mFloor->Draw(*mWindow);
	mCanon->Draw(*mWindow);
	if (mRagdoll != nullptr) { mRagdoll->Draw(*mWindow); }
}

bool Game::NextLevel()
{

	if (mState = LEVEL1)
	{
		mState = NEWMENU;
	}
	else if (mState = NEWMENU)
	{
		mState = LEVEL2;
	}
	else if (mState = LEVEL2)
	{
		mState = MENU;
	}
	else if (mState = MENU)
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
	    mUI->DrawMenu(*mWindow);
	    break; 
	case LEVEL1: 
		if (mBox[0] == nullptr) mBox[0] = new Box(*mWorld, { 70.f, 100.5f });
		if (mBox[1] == nullptr) mBox[1] = new Box(*mWorld, { 70.f, 110.5f });
		if (mBox[2] == nullptr) mBox[2] = new Box(*mWorld, { 70.f, 120.5f });
		if (mBox[3] == nullptr) mBox[3] = new Box(*mWorld, { 70.f, 130.5f });
		if (mBox[4] == nullptr) mBox[4] = new Box(*mWorld, { 70.f, 140.5f });
		if (mCircleOfFire == nullptr) mCircleOfFire = new CircleOfFire(*mWorld, { 120.f, 140.5f });
	    RunLevel1(); 
	    break; 
	case NEWMENU:
		mUI->DrawNewMenu(*mWindow);
		break;
	case LEVEL2: 
		if (mBox == nullptr) mBox[0] = new Box(*mWorld, { 110.f, 140.5f });
	    RunLevel2();
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
	delete mClock;
	delete mInitTime;
	delete mCamara;
	delete mEvent;
	delete mUI;
	delete mCountdownTimer;
}