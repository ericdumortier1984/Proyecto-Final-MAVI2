#pragma once
#include "Level.h"
#include "Wheel.h"
#include "EmptyCans.h"
#include "Box.h"

class Level3 : public Level
{
public:

	Level3(int mWidth, int mHeight, bool mUnlocked);
	~Level3();

	bool FinishLevel() override;
	bool UnlockedLevel() const override;

protected:

	void RunLevel() override;

private:

	Wheel* mWheel;
	EmptyCans* mEmptyCans;
	Box* mBox;

	ContactListener* mContactListener;

	void CheckCollisions();

	bool mUnlocked;
};

