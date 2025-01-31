#pragma once
#include "mainHeader.h"
#include "ContactListener.h"
#include "Avatar.h"
#include "Floor.h"
#include "Canon.h"
#include "Ragdoll.h"

class Level3
{
public:

	Level3(int mWidth, int mHeight);
	~Level3();

	bool FinishLevel3();
	void Run();

private:

	RenderWindow* mWindow;
	Event* mEvent;
	View* mCamara;
	Clock* mClock;
	Time* mInitTime;

	Font* mFont;
	Text* mCountdownTimer;
	Text* mRagdollCounter;

	b2World* mWorld;

	Floor* mFloor;
	Canon* mCanon;
	Ragdoll* mRagdoll;

	ContactListener* mContactListener;

	enum TimeLimits { LEVEL1_TIME_LIMIT = 60, LEVEL2_TIME_LIMIT = 60, LEVEL3_TIME_LIMIT = 60 };
	TimeLimits mTimeLimits;

	float mFps, mFrameTime, mActualTime, mElapsedTime;
	bool  mLevelFinish;
	int   mRagdollCount;

	void SetCamara(float mZoom);
	void CheckCollisions();
	void InitPhysics();
	void UpdatePhysics();
	void ProcessEvents();
	void Update();
	void RunLevel();
	void Draw();
};
