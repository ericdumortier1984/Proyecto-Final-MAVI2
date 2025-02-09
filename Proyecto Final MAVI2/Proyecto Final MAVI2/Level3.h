#pragma once
#include "Level.h"
#include "Wheel.h"
#include "EmptyCans.h"
#include "Box.h"
#include "StaticBox.h"
#include "DynamicPlatform.h"
#include "StaticPlatform.h"

class Level3 : public Level
{
public:

	Level3(int mWidth, int mHeight, bool mUnlocked);
	~Level3();

	bool FinishLevel() override;
	bool UnlockedLevel() const override;
	bool GetHurt();
	void ShowLoseMsg();

protected:

	void RunLevel() override;

private:

	Wheel* mWheel[10];
	EmptyCans* mEmptyCans;
	Box* mBox[20];
	StaticBox* mStaticBox[10];
	DynamicPlatform* mDynamicPlatform[10];
	StaticPlatform* mStaticPlatform[10];

	ContactListener* mContactListener;

	void CheckCollisions();

	bool mUnlocked;
	bool mGetHurt;
};

