#pragma once
#include "Level.h"

class Level3 : public Level
{
public:

	Level3(int mWidth, int mHeight);
	~Level3();

	bool FinishLevel() override;

protected:

	void RunLevel() override;

private:

	ContactListener* mContactListener;

	void CheckCollisions();
};

