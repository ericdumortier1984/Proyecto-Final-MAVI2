#include "Level3.h"

Level3::Level3(int mWidth, int mHeight) : Level(mWidth, mHeight)
{
	// Inicializacion de objetos específicos de Level3

	mContactListener = new ContactListener(this);

	CheckCollisions();
}

Level3::~Level3()
{
	// Liberar recursos específicos de Level3
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
	mWindow->draw(*mCountdownTimer);
	mWindow->draw(*mRagdollCounter);
	mWindow->draw(*mCrosshairSp);
	mWindow->display();
}
