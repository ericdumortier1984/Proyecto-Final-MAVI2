#include "Level3.h"

Level3::Level3(int mWidth, int mHeight) : Level(mWidth, mHeight)
{
	

	mContactListener = new ContactListener(this);

	CheckCollisions();

	if (mWheel == nullptr) mWheel = new Wheel(*mWorld, { 50.f, 50.f });
	if (mBox == nullptr) mBox = new Box(*mWorld, { 50.f, 60.f });
}

Level3::~Level3()
{
	delete mWheel;
	delete mBox;
}

void Level3::CheckCollisions()
{

	mWorld->SetContactListener(mContactListener);
}

bool Level3::FinishLevel()
{
	mWindow->close();
	return true;
}

void Level3::RunLevel()
{
	mWindow->clear(Color(255, 218, 185)); // PeachPuff
	SetCamara(0.20f);
	mWindow->setMouseCursorVisible(false);

	mFloor->Draw(*mWindow);
	mCanon->Draw(*mWindow);
	if (mRagdoll != nullptr) { mRagdoll->Draw(*mWindow); }
	if (mWheel != nullptr) { mWheel->Draw(*mWindow); }
	if (mBox != nullptr) { mBox->Draw(*mWindow); }
	for (int i = 0; i < 3; i++) { mWindow->draw(*mUIsp[i]); }
	mWindow->draw(*mCountdownTimer);
	mWindow->draw(*mRagdollCounter);
	mWindow->draw(*mCanonPower);
	mWindow->draw(*mCrosshairSp);
	mWindow->display();
}
