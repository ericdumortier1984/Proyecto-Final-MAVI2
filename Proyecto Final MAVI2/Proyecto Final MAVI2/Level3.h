#pragma once
#include "Level.h"
#include "Wheel.h"
#include "Box.h"

class Level3 : public Level
{
public:

	Level3(int mWidth, int mHeight);
	~Level3();

	bool FinishLevel() override;

protected:

	void RunLevel() override;

private:

	Wheel* mWheel;
	Box* mBox;

	ContactListener* mContactListener;

	void CheckCollisions();
};

