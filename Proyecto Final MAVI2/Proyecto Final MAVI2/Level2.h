#pragma once
#include "Level.h"
#include "Pulley.h"
#include "Box.h"
#include "Balloons.h"

class Level2 : public Level
{
public:

	Level2(int mWidth, int mHeight);
	~Level2();

	bool FinishLevel() override;

protected:

	void RunLevel() override;

private:

	Box* mBox[10];
	Pulley* mPulley[10];
	Balloons* mBalloons;

	ContactListener* mContactListener;

	void CheckCollisions();
};

