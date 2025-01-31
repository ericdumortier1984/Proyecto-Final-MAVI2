#pragma once
#include "mainHeader.h"
#include "ContactListener.h"
#include "Avatar.h"
#include "Floor.h"
#include "Canon.h"
#include "Ragdoll.h"
#include "CircleOfFire.h"
#include "Pendulum.h"
#include "Box.h"

class Level1
{
public:

	Level1(int mWidth, int mHeight);
	~Level1();

	bool FinishLevel1();
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

	Texture* mCrosshairTx;
	Sprite* mCrosshairSp;

	Floor* mFloor;
	Canon* mCanon;
	Ragdoll* mRagdoll;
	Box* mBox[10];
	CircleOfFire* mCircleOfFire;
	Pendulum* mPendulum[10];

	ContactListener* mContactListener;

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