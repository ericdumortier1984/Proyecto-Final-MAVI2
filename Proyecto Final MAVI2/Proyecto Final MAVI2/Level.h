#pragma once
#include "mainHeader.h"
#include "ContactListener.h"
#include "Avatar.h"
#include "Floor.h"
#include "Canon.h"
#include "Ragdoll.h"

class Level
{
public:

    Level(int mWidth, int mHeight);
    virtual ~Level();

    virtual bool FinishLevel() = 0;
    void Run();

protected:

    RenderWindow* mWindow;
    Event* mEvent;
    View* mCamara;
    Clock* mClock;
    Time* mInitTime;

    Font* mFont;
    Text* mCountdownTimer;
    Text* mRagdollCounter;
    Text* mCanonPower;
    Text* mStateMsg;
    b2World* mWorld;

    Texture* mCrosshairTx;
    Sprite* mCrosshairSp;

    Texture* mUItx[3];
    Sprite* mUIsp[3];

    Floor* mFloor;
    Canon* mCanon;
    Ragdoll* mRagdoll;

    float mFps, mFrameTime, mActualTime, mElapsedTime;
    bool  mLevelFinish;
    int   mRagdollCount;

    void SetCamara(float mZoom);
    void InitPhysics();
    void UpdatePhysics();
    void ProcessEvents();
    void Update();
    virtual void RunLevel() = 0;
    void ShowMsg(const string& mMessage);
    void Draw();
};