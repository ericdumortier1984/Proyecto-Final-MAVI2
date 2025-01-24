#include "Avatar.h"
#include "Floor.h"
#include "Ragdoll.h"
#include "Box.h"
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
	void Run();

private:

	RenderWindow* mWindow;
	Event* mEvent;
	View* mCamara;
	Clock* mClock;
	Time* mInitTime;

	Font* mFont;
	Text* mCountdownTimer;

	b2World* mWorld;

	UI* mUI;
	Floor* mFloor;
	Canon* mCanon;
	Ragdoll* mRagdoll;
	Box* mBox[10];
	CircleOfFire* mCircleOfFire;

	ContactListener* mContactListener;
	
	enum GameState { MENU, LEVEL1, NEWMENU, LEVEL2, EXIT };
	GameState mState;
	enum TimeLimits { LEVEL1_TIME_LIMIT = 34, LEVEL2_TIME_LIMIT = 34 };
	TimeLimits mTimeLimits;

	float mFps, mFrameTime, mActualTime;
	bool nextLevel;

	void SetCamara(float mZoom);
	void CheckCollisions();
	void InitPhysics();
	void UpdatePhysics();
	void ProcessEvents();
	void Update();
	void RunLevel1();
	void RunLevel2();
	void Draw();
};

