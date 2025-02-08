#pragma once
#include "Level.h"
#include "Pulley.h"
#include "Box.h"
#include "StaticBox.h"
#include "DynamicPlatform.h"
#include "Balloons.h"

class Level2 : public Level
{
public:

	Level2(int mWidth, int mHeight, bool mUnlocked);
	~Level2();

	bool FinishLevel() override;
	bool UnlockedLevel() const override;

protected:

	void RunLevel() override;

private:

	Box* mBox[20];
	StaticBox* mStaticBox[10];
	Pulley* mPulley[10];
	Balloons* mBalloons;
	DynamicPlatform* mDynamicPlatform[10];

	ContactListener* mContactListener;

	void CheckCollisions();

	bool mUnlocked;
};

