#include "Level1.h"

Level1::Level1(int mWidth, int mHeight, bool mUnlocked) : Level(mWidth, mHeight, mUnlocked), mUnlocked(mUnlocked)
{

	cout << "[LEVEL 1]" << endl; // Debug

	mContactListener = new ContactListener(this);

	CheckCollisions();

	if (mPendulum[0] == nullptr) mPendulum[0] = new Pendulum(*mWorld, { -10.f, 105.f });
	if (mPendulum[1] == nullptr) mPendulum[1] = new Pendulum(*mWorld, { 10.f, 95.f });
	if (mPendulum[2] == nullptr) mPendulum[2] = new Pendulum(*mWorld, { 30.f, 85.f });
	if (mBox[0] == nullptr) mBox[0] = new Box(*mWorld, { 60.f, 120.5f });
	if (mBox[1] == nullptr) mBox[1] = new Box(*mWorld, { 60.f, 130.5f });
	if (mBox[2] == nullptr) mBox[2] = new Box(*mWorld, { 60.f, 140.5f });
	if (mCircleOfFire == nullptr) mCircleOfFire = new CircleOfFire(*mWorld, { 120.f, 140.5f });
}

Level1::~Level1()
{
	for (int i = 0; i < 10; ++i)
	{
		delete mPendulum[i];
		delete mBox[i];
	}
	delete mCircleOfFire;
}

void Level1::CheckCollisions()
{

	mWorld->SetContactListener(mContactListener);
}

bool Level1::UnlockedLevel() const
{
	return mUnlocked;
}

bool Level1::FinishLevel()
{
	if (!mLevelFinish)
	{
		mLevelFinish = true;
		mLevelMusic->stop();
		mVictorySound->play();
		mStateMsg->setPosition(-20.f, 55.f);
		ShowMsg("LEVEL WIN");
	}
	return true;
}

void Level1::RunLevel()
{

	mWindow->clear(Color(173, 216, 230)); //  LightBlue
	SetCamara(0.20f);
	mWindow->setMouseCursorVisible(false);

	mFloor->Draw(*mWindow);
	mCanon->Draw(*mWindow);
	for (int i = 0; i < 3; i++) { if (mPendulum[i] != nullptr) mPendulum[i]->Draw(*mWindow); }
	for (int i = 0; i < 3; ++i) { if (mBox[i] != nullptr) mBox[i]->Draw(*mWindow); }
	if (mCircleOfFire != nullptr) { mCircleOfFire->Draw(*mWindow); }
	if (mRagdoll != nullptr) { mRagdoll->Draw(*mWindow); }
	for (int i = 0; i < 3; i++) { mWindow->draw(*mUIsp[i]); }
	mWindow->draw(*mCountdownTimer);
	mWindow->draw(*mRagdollCounter);
	mWindow->draw(*mCanonPower);
	mWindow->draw(*mCrosshairSp);
	mWindow->display();
}
