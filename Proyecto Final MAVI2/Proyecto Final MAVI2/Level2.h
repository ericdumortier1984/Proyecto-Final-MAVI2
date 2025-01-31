#pragma once
#include "mainHeader.h"
#include "ContactListener.h"
#include "Avatar.h"
#include "Floor.h"
#include "Canon.h"
#include "Ragdoll.h"
#include "Pulley.h"
#include "Box.h"

class Level2
{
public:

	Level2(int mWidth, int mHeight);
	~Level2();

	bool FinishLevel2();
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
	Box* mBox[10];
	Pulley* mPulley[10];

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
