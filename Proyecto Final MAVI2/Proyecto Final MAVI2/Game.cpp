#include "Game.h"

Game::Game() : mState(MENU), mFps(60.f), mFrameTime(1.f / mFps), mActualTime(0.f), mNextLevel(false), mRagdollCount(0)
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

	mRagdollCounter = new Text;
	mRagdollCounter->setFont(*mFont);
	mRagdollCounter->setCharacterSize(12);
	mRagdollCounter->setPosition(-80.f, 28.f);
	mRagdollCounter->setFillColor(Color::White);
	mRagdollCounter->setOutlineThickness(1);
	mRagdollCounter->setOutlineColor(Color::Black);

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

	for (b2Body* body : mBodiesToDestroy) //Destruir los cuerpos pendientes después del paso de simulación
	{
		mWorld->DestroyBody(body);
	}
	mBodiesToDestroy.clear();
}

void Game::Run() 
{ 

	while (mWindow->isOpen()) 
	{ 
		*mInitTime = mClock->getElapsedTime();

		if (mActualTime + mFrameTime < mInitTime->asSeconds())
		{
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
					if (mUI->IsPlayButtonClicked(mEvent->mouseButton.x, mEvent->mouseButton.y))
					{
						mState = LEVEL1;
						cout << "[LEVEL 1]" << endl;
						mClock->restart();
					}
					else if (mUI->IsExitButtonClicked(mEvent->mouseButton.x, mEvent->mouseButton.y))
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
					mRagdollCount++;
					mRagdollCounter->setString("Ragdolls: " + to_string(mRagdollCount));
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
		timeRemaining = static_cast<int>(LEVEL1_TIME_LIMIT) - mClock->getElapsedTime().asSeconds();
		//cout << "[CRONOMETRO LEVEL 1]" << endl; //Debug
		//cout << "[TIME REMAINING: ]" << timeRemaining << endl; // Debug
		if (timeRemaining <= 0)
		{
			if (mState == PAUSE) return;
			cout << "[TIME UP LEVEL 1]" << endl; // Debug
			mState = EXIT;
		}
	} 
	else if (mState == LEVEL2)
	{
		timeRemaining = static_cast<int>(LEVEL2_TIME_LIMIT) - mClock->getElapsedTime().asSeconds();
		if (timeRemaining <= 0)
		{
			cout << "[TIME UP LEVEL 2]" << endl;
			mState = EXIT;
		}
	}
	else if (mState == LEVEL3)
	{
		timeRemaining = static_cast<int>(LEVEL3_TIME_LIMIT) - mClock->getElapsedTime().asSeconds();
		if (timeRemaining <= 0)
		{
			cout << "[TIME UP LEVEL 3]" << endl;
			mState = EXIT;
		}
	}

	int seconds = static_cast<int>(timeRemaining) % 34;
	mCountdownTimer->setString("TIME: " + to_string(seconds));
}

void Game::RunLevel(GameState mState)
{
	switch (mState)
	{
	case LEVEL1:
		SetCamara(0.20f);
		mWindow->setMouseCursorVisible(false);
		mUI->SetImages(*mWindow);

		mUI->DrawImages(*mWindow);
		mFloor->Draw(*mWindow);
		mCanon->Draw(*mWindow);
		for (int i = 0; i < 5; ++i) { if (mBox[i] != nullptr) mBox[i]->Draw(*mWindow); }
		if (mCircleOfFire != nullptr) { mCircleOfFire->Draw(*mWindow); }
		if (mRagdoll != nullptr) { mRagdoll->Draw(*mWindow); }
		mWindow->draw(*mCountdownTimer);
		mWindow->draw(*mRagdollCounter);
		break;

	case LEVEL2:
		SetCamara(0.20f);
		mWindow->setMouseCursorVisible(false);
		mUI->SetImages(*mWindow);

		mUI->DrawImages(*mWindow);
		mFloor->Draw(*mWindow);
		mCanon->Draw(*mWindow);

		for (int i = 0; i < 5; ++i) { if (mBox[i] != nullptr) mBox[i]->Draw(*mWindow); }
		if (mSaw != nullptr) { mSaw->Draw(*mWindow); }
		if (mRagdoll != nullptr) { mRagdoll->Draw(*mWindow); }
		mWindow->draw(*mCountdownTimer);
		mWindow->draw(*mRagdollCounter);
		break;

	case LEVEL3:
		SetCamara(0.20f);
		mWindow->setMouseCursorVisible(false);
		mUI->SetImages(*mWindow);

		mUI->DrawImages(*mWindow);
		mFloor->Draw(*mWindow);
		mCanon->Draw(*mWindow);
		
		for (int i = 0; i < 5; ++i) { if (mBox[i] != nullptr) mBox[i]->Draw(*mWindow); }
		if (mNewBox != nullptr) { mNewBox->Draw(*mWindow); }
		if (mRagdoll != nullptr) { mRagdoll->Draw(*mWindow); }
		mWindow->draw(*mCountdownTimer);
		mWindow->draw(*mRagdollCounter);
		break;

	default:
		break;
	}
}

bool Game::NextLevel()
{
	
	if (mState = LEVEL1)
	{
		ClearLevel(); 
		mState = LEVEL2;
		cout << "[LEVEL 2]" << endl;
		mRagdollCount = 0;
		mClock->restart();

		return mNextLevel = true;
	}

	return false;
}

bool Game::NextLevel2()
{

	if (mState = LEVEL2)
	{
		ClearLevel(); 
		mState = LEVEL3;
		cout << "[LEVEL 3]" << endl;
		mRagdollCount = 0;
		mClock->restart();

		return true;
	}

	return false;
}

bool Game::NextLevel3()
{

	if (mState = LEVEL3)
	{
		ClearLevel(); 
		mState = EXIT;
		mRagdollCount = 0;
		mClock->restart();
		cout << "[EXIT GAME]" << endl;
		return true;
	}

	return false;
}

void Game::ClearLevel()
{
	// Eliminar los Box
	for (int i = 0; i < 10; ++i)
	{
		if (mBox[i] != nullptr)
		{
			mBodiesToDestroy.push_back(mBox[i]->GetBody());
			delete mBox[i];
			mBox[i] = nullptr;
		}
	}

	// Eliminar el Ragdoll
	if (mRagdoll != nullptr)
	{
		delete mRagdoll;
		mRagdoll = nullptr;
	}

	// Eliminar el CircleOfFire
	if (mCircleOfFire != nullptr)
	{
		mBodiesToDestroy.push_back(mCircleOfFire->GetBody());
		delete mCircleOfFire;
		mCircleOfFire = nullptr;
	}

	// Eliminar el newBox
	if (mNewBox != nullptr)
	{
		mBodiesToDestroy.push_back(mNewBox->GetBody());
		delete mNewBox;
		mNewBox = nullptr;
	}

	// Eliminar el Saw
	if (mSaw != nullptr)
	{
		mBodiesToDestroy.push_back(mSaw->GetBody());
		delete mSaw;
		mSaw = nullptr;
	}
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
		mWindow->clear(Color(173, 216, 230)); //  LightBlue
		if (mBox[0] == nullptr) mBox[0] = new Box(*mWorld, { 70.f, 100.5f });
		if (mBox[1] == nullptr) mBox[1] = new Box(*mWorld, { 70.f, 110.5f });
		if (mBox[2] == nullptr) mBox[2] = new Box(*mWorld, { 70.f, 120.5f });
		if (mBox[3] == nullptr) mBox[3] = new Box(*mWorld, { 70.f, 130.5f });
		if (mBox[4] == nullptr) mBox[4] = new Box(*mWorld, { 70.f, 140.5f });
		if (mCircleOfFire == nullptr) mCircleOfFire = new CircleOfFire(*mWorld, { 120.f, 140.5f });
		RunLevel(LEVEL1);
		break;

	case LEVEL2:
		mWindow->clear(Color(255, 182, 193)); // LightPink
		if (mBox[0] == nullptr) mBox[0] = new Box(*mWorld, { 50.f, 100.5f });
		if (mBox[1] == nullptr) mBox[1] = new Box(*mWorld, { 50.f, 110.5f });
		if (mBox[2] == nullptr) mBox[2] = new Box(*mWorld, { 50.f, 120.5f });
		if (mBox[3] == nullptr) mBox[3] = new Box(*mWorld, { 50.f, 130.5f });
		if (mBox[4] == nullptr) mBox[4] = new Box(*mWorld, { 50.f, 140.5f });
		if (mSaw == nullptr) mSaw = new Saw(*mWorld, { -50.f, 90.5f });
		RunLevel(LEVEL2);
		break;

	case LEVEL3:
		mWindow->clear(Color(255, 218, 185)); // PeachPuff
		if (mBox[0] == nullptr) mBox[0] = new Box(*mWorld, { 30.f, 100.5f });
		if (mBox[1] == nullptr) mBox[1] = new Box(*mWorld, { 30.f, 110.5f });
		if (mBox[2] == nullptr) mBox[2] = new Box(*mWorld, { 30.f, 120.5f });
		if (mBox[3] == nullptr) mBox[3] = new Box(*mWorld, { 30.f, 130.5f });
		if (mBox[4] == nullptr) mBox[4] = new Box(*mWorld, { 30.f, 140.5f });
		if (mNewBox == nullptr) mNewBox = new NewBox(*mWorld, { 40.f, 100.5f });
		RunLevel(LEVEL3);
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