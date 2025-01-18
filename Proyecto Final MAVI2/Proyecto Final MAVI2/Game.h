#include "Avatar.h"
#include "Floor.h"
#include "Ragdoll.h"
#include "Box.h"
#include "Canon.h"
#include "ContactListener.h"

class Game 
{
public:

	Game();
	~Game();

	void Run();

private:

	RenderWindow* mWindow;
	Event* mEvent;
	View* mCamara;
	Clock* mClock;
	Time* mInitTime;

	Font* mFont;
	Text* mTitle;
	Text* mPlay;
	Text* mExit;
	Text* mNextLevel;

	b2World* mWorld;

	Floor* mFloor;
	Canon* mCanon;
	Ragdoll* mRagdoll;
	Box* mBox;

	ContactListener* mContactListener;

	//SFML
	Texture* mCrosshairTx;
	Texture* mBackMenuTx;
	Texture* mBackLv1Tx;

	Sprite* mCrosshairSp;
	Sprite* mBackMenuSp;
	Sprite* mBackLv1Sp;

	enum GameState { MENU, LEVEL1, LEVEL2, LEVEL3, EXIT };
	GameState mState;

	float mFps, mFrameTime, mActualTime;
	bool winLevel;
	bool nextLevel;

	void SetCamara(float mZoom);
	void SetImages();
	void SetMenu();
	void CheckCollisions();
	void CheckWin();
	void InitPhysics();
	void UpdatePhysics();
	void ProcessEvents();
	void Update();
	void DrawMenu();
	void RunLevel();
	void RunLevel2();
	void RunLevel3();
	void Draw();
};

