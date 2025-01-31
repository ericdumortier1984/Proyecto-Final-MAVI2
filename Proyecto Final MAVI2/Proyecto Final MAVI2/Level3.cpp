#include "Level3.h"

Level3::Level3(int mWidth, int mHeight) : mFps(60.f), mFrameTime(1.f / mFps), mActualTime(0.f), mLevelFinish(false), mRagdollCount(0)
{

	mWindow = new RenderWindow(VideoMode(1280, 720), "LEVEL 3");
	mWindow->setFramerateLimit(mFps);

	mContactListener = new ContactListener(this);

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

void Level3::SetCamara(float mZoom)
{

	mCamara->setSize(mWindow->getSize().x * mZoom, mWindow->getSize().y * mZoom);
	mCamara->setCenter(20, 100);
	mWindow->setView(*mCamara);
}

void Level3::InitPhysics()
{

	mWorld = new b2World({ 0.f, 9.8f });
}

void Level3::CheckCollisions()
{

	mWorld->SetContactListener(mContactListener);
}

void Level3::UpdatePhysics()
{

	mWorld->Step(mFrameTime, 8, 8);
	mWorld->ClearForces();
}

void Level3::Run()
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

void Level3::ProcessEvents()
{
	while (mWindow->pollEvent(*mEvent))
	{
		if (mEvent->type == Event::Closed)
		{
			mWindow->close();
		}

		if (mEvent->type == Event::MouseButtonPressed)
		{
			Vector2f mPositionMouse;
			mPositionMouse = mWindow->mapPixelToCoords(Mouse::getPosition(*mWindow));
			mCanon->Shoot(mWorld, mPositionMouse, *mWindow);
			mRagdoll = mCanon->GetRagdoll();
			mRagdollCount++;
			mRagdollCounter->setString("Ragdolls: " + to_string(mRagdollCount));
		}

		if (mEvent->type == Event::MouseMoved)
		{
			Vector2f mPositionMouse;
			mPositionMouse = mWindow->mapPixelToCoords(Mouse::getPosition(*mWindow));
			mCanon->Update(mPositionMouse);
		}
	}
}

void Level3::Update()
{

	float mTimeRemaining = 0.f;
	float elapsedTime = mClock->getElapsedTime().asSeconds();
	mTimeRemaining = 60.f - elapsedTime;

	if (mTimeRemaining <= 0)
	{
		cout << "[TIME UP LEVEL 3]" << endl; // Debug
	}

	int seconds = static_cast<int>(mTimeRemaining) % 60;
	mCountdownTimer->setString("TIME: " + to_string(seconds));
}

void Level3::RunLevel()
{

	SetCamara(0.20f);
	mWindow->setMouseCursorVisible(true);

	mFloor->Draw(*mWindow);
	mCanon->Draw(*mWindow);
	if (mRagdoll != nullptr) { mRagdoll->Draw(*mWindow); }
	mWindow->draw(*mCountdownTimer);
	mWindow->draw(*mRagdollCounter);
}

bool Level3::FinishLevel3()
{


	return false;
}

void Level3::Draw()
{

	mWindow->clear(Color(255, 218, 185)); // PeachPuff
	RunLevel();
	mWindow->display();
}

Level3::~Level3()
{

	delete mWindow;
	delete mFont;
	delete mClock;
	delete mInitTime;
	delete mCamara;
	delete mEvent;
	delete mCountdownTimer;
	delete mRagdollCounter;
	delete mContactListener;
}