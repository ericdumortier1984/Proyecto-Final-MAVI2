#include "Level2.h"

Level2::Level2(int mWidth, int mHeight) : Level(mWidth, mHeight)
{

	mContactListener = new ContactListener(this);

	CheckCollisions();

	//Poleas
	if (mPulley[0] == nullptr) mPulley[0] = new Pulley(*mWorld, { -25.f, 90.f });
	if (mPulley[1] == nullptr) mPulley[1] = new Pulley(*mWorld, { 30.f, 80.f });
	if (mPulley[2] == nullptr) mPulley[2] = new Pulley(*mWorld, { 80.f, 70.f });
	
	//Cajas
	if (mBox[0] == nullptr) mBox[0] = new Box(*mWorld, { -40.3f, 110.5f });
	if (mBox[1] == nullptr) mBox[1] = new Box(*mWorld, { -39.98f, 120.5f });
	if (mBox[2] == nullptr) mBox[2] = new Box(*mWorld, { -39.99f, 130.5f });
	if (mBox[3] == nullptr) mBox[3] = new Box(*mWorld, { 14.9f, 100.5f });
	if (mBox[4] == nullptr) mBox[4] = new Box(*mWorld, { 15.08f, 110.5f });
	if (mBox[5] == nullptr) mBox[5] = new Box(*mWorld, { 14.998f, 120.5f });
	if (mBox[6] == nullptr) mBox[6] = new Box(*mWorld, { 64.9f, 90.5f });
	if (mBox[7] == nullptr) mBox[7] = new Box(*mWorld, { 65.08f, 100.5f });
	if (mBox[8] == nullptr) mBox[8] = new Box(*mWorld, { 64.998f, 110.5f });

	//Globos
	if (mBalloons == nullptr) mBalloons = new Balloons(*mWorld, { 120.f, 100.f });

}

Level2::~Level2()
{
	for (int i = 0; i < 10; ++i)
	{
		delete mPulley[i];
		delete mBox[i];
	}

	delete mBalloons;
}

void Level2::CheckCollisions()
{

	mWorld->SetContactListener(mContactListener);
}

bool Level2::FinishLevel()
{
	mWindow->close();
	return true;
}

void Level2::RunLevel()
{

	mWindow->clear(Color(255, 182, 193)); // LightPink
	SetCamara(0.20f);
	mWindow->setMouseCursorVisible(false);

	mFloor->Draw(*mWindow);
	mCanon->Draw(*mWindow);
	for (int i = 0; i < 3; i++) { if (mPulley[i] != nullptr) mPulley[i]->Draw(*mWindow); }
	for (int i = 0; i < 9; ++i) { if (mBox[i] != nullptr) mBox[i]->Draw(*mWindow); }
	if (mBalloons != nullptr) { mBalloons->Draw(*mWindow); };
	if (mRagdoll != nullptr) { mRagdoll->Draw(*mWindow); }
	mWindow->draw(*mCountdownTimer);
	mWindow->draw(*mRagdollCounter);
	mWindow->draw(*mCrosshairSp);
	mWindow->display();
}
