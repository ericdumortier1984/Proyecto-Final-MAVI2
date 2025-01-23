#include "Avatar.h"
#include "Floor.h"
#include "Ragdoll.h"
#include "Box.h"
#include "CircleOfFire.h"
#include "Canon.h"
#include "ContactListener.h"

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
	Text* mNextLevel;
	Text* mCountdownTimer;
	Text* mText;
	Text* mPlayText;
	Text* mExitText;

	b2World* mWorld;

	Floor* mFloor;
	Canon* mCanon;
	Ragdoll* mRagdoll;
	Box* mBox[10];
	CircleOfFire* mCircleOfFire;

	ContactListener* mContactListener;

	//SFML
	Texture* mCrosshairTx;
	Texture* mBackMenuTx;
	Texture* mTitleTx;
	Texture* mButtonPlayTx;
	Texture* mButtonExitTx;
	Texture* mBackLv1Tx;

	Sprite* mCrosshairSp;
	Sprite* mBackMenuSp;
	Sprite* mTitleSp;
	Sprite* mButtonPlaySp;
	Sprite* mButtonExitSp;
	Sprite* mBackLv1Sp;

	enum GameState { MENU, LEVEL1, LEVEL2, EXIT };
	GameState mState;
	enum TimeLimits { LEVEL1_TIME_LIMIT = 180, LEVEL2_TIME_LIMIT = 300 };
	TimeLimits mTimeLimits;

	float mFps, mFrameTime, mActualTime;
	bool nextLevel;
	bool lostLevel;

	void SetCamara(float mZoom);
	void SetImages();
	void SetMenu();
	void CheckCollisions();
	void InitPhysics();
	void UpdatePhysics();
	void ProcessEvents();
	void Update();
	void RunLevel1();
	void RunLevel2();
	void DrawMenu();
	void Draw();
};

