#pragma once
#include "Level.h"
#include "CircleOfFire.h"
#include "Pendulum.h"
#include "Box.h"
#include "StaticBox.h"

class Level1 : public Level
{
public:

	Level1(int mWidth, int mHeight, bool mUnlocked);
	~Level1();

	bool FinishLevel() override;
	bool UnlockedLevel() const override;

protected:

	void RunLevel() override;

private:

	CircleOfFire* mCircleOfFire;
	Pendulum* mPendulum[10];
	Box* mBox[10];
	StaticBox* mStaticBox[10];

	ContactListener* mContactListener;

	void CheckCollisions();

	bool mUnlocked;
};
