#include "Avatar.h"
#include "Floor.h"
#include "Ragdoll.h"
#include "Box.h"
#include "NewBox.h"
#include "Saw.h"
#include "CircleOfFire.h"
#include "Canon.h"
#include "ContactListener.h"
#include "UI.h"

class Game 
{
public:

	Game();
	~Game();

	bool NextLevel();
	bool NextLevel2();
	bool NextLevel3();
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

	UI* mUI;
	Floor* mFloor;
	Canon* mCanon;
	Ragdoll* mRagdoll;
	Box* mBox[10];
	CircleOfFire* mCircleOfFire;
	NewBox* mNewBox;
	Saw* mSaw;


	ContactListener* mContactListener;
	
	enum GameState { MENU, INFORMATION, LEVEL1, LEVEL2, LEVEL3, PAUSE, EXIT };
	GameState mState;
	enum TimeLimits { LEVEL1_TIME_LIMIT = 34, LEVEL2_TIME_LIMIT = 34, LEVEL3_TIME_LIMIT = 34};
	TimeLimits mTimeLimits;

	float mFps, mFrameTime, mActualTime, mElapsedTime;
	bool  mNextLevel;
	int   mRagdollCount;

	void SetCamara(float mZoom);
	void CheckCollisions();
	void InitPhysics();
	void UpdatePhysics();
	void ProcessEvents();
	void Update();
	void RunLevel(GameState mState);
	void ClearLevel();
	void Draw();

	vector<b2Body*> mBodiesToDestroy; // Copilot IA
};

