#include "Level2.h"

Level2::Level2(int mWidth, int mHeight) : mFps(60.f), mFrameTime(1.f / mFps), mActualTime(0.f), mLevelFinish(false), mRagdollCount(0)
{

	mWindow = new RenderWindow(VideoMode(1280, 720), "LEVEL 1");
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

void Level2::SetCamara(float mZoom)
{

	mCamara->setSize(mWindow->getSize().x * mZoom, mWindow->getSize().y * mZoom);
	mCamara->setCenter(20, 100);
	mWindow->setView(*mCamara);
}

void Level2::InitPhysics()
{

	mWorld = new b2World({ 0.f, 9.8f });
}

void Level2::CheckCollisions()
{

	mWorld->SetContactListener(mContactListener);
}

void Level2::UpdatePhysics()
{

	mWorld->Step(mFrameTime, 8, 8);
	mWorld->ClearForces();
}

void Level2::Run()
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

void Level2::ProcessEvents()
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

void Level2::Update()
{

	float mTimeRemaining = 0.f;
	float elapsedTime = mClock->getElapsedTime().asSeconds();
	mTimeRemaining = 60.f - elapsedTime;

	if (mTimeRemaining <= 0)
	{
		cout << "[TIME UP LEVEL 1]" << endl; // Debug
	}

	int seconds = static_cast<int>(mTimeRemaining) % 60;
	mCountdownTimer->setString("TIME: " + to_string(seconds));
}

void Level2::RunLevel()
{

	SetCamara(0.20f);
	mWindow->setMouseCursorVisible(true);

	mFloor->Draw(*mWindow);
	mCanon->Draw(*mWindow);

	for (int i = 0; i < 3; i++) { if (mPulley[i] != nullptr) mPulley[i]->Draw(*mWindow); }
	for (int i = 0; i < 9; ++i) { if (mBox[i] != nullptr) mBox[i]->Draw(*mWindow); }
	
	if (mRagdoll != nullptr) { mRagdoll->Draw(*mWindow); }
	mWindow->draw(*mCountdownTimer);
	mWindow->draw(*mRagdollCounter);
}

bool Level2::FinishLevel2()
{



	return false;
}

void Level2::Draw()
{

	mWindow->clear(Color(255, 182, 193)); // LightPink
	if (mPulley[0] == nullptr) mPulley[0] = new Pulley(*mWorld, { -25.f, 90.f });
	if (mPulley[1] == nullptr) mPulley[1] = new Pulley(*mWorld, { 30.f, 80.f });
	if (mPulley[2] == nullptr) mPulley[2] = new Pulley(*mWorld, { 80.f, 70.f });
	if (mBox[0] == nullptr) mBox[0] = new Box(*mWorld, { -40.3f, 110.5f });
	if (mBox[1] == nullptr) mBox[1] = new Box(*mWorld, { -39.98f, 120.5f });
	if (mBox[2] == nullptr) mBox[2] = new Box(*mWorld, { -39.99f, 130.5f });
	if (mBox[3] == nullptr) mBox[3] = new Box(*mWorld, { 14.9f, 100.5f });
	if (mBox[4] == nullptr) mBox[4] = new Box(*mWorld, { 15.08f, 110.5f });
	if (mBox[5] == nullptr) mBox[5] = new Box(*mWorld, { 14.998f, 120.5f });
	if (mBox[6] == nullptr) mBox[6] = new Box(*mWorld, { 64.9f, 90.5f });
	if (mBox[7] == nullptr) mBox[7] = new Box(*mWorld, { 65.08f, 100.5f });
	if (mBox[8] == nullptr) mBox[8] = new Box(*mWorld, { 64.998f, 110.5f });
	RunLevel();
	mWindow->display();
}

Level2::~Level2()
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