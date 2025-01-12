#include "Avatar.h"
#include "Ragdoll.h"

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

	Ragdoll* mRagdoll;

	//Box2D
	b2Body* mBodyCanon;
	b2BodyDef mBodyDefCanon;
	b2Fixture* mFixtureCanon;
	b2FixtureDef mFixtureDefCanon;

	b2Body* mBodyFloor;
	b2BodyDef mBodyDefFloor;
	b2Fixture* mFixtureFloor;
	b2FixtureDef mFixtureDefFloor;
	
	//SFML
	Texture* mCrosshairTx;
	Texture* mBackMenuTx;
	Texture* mBackLv1Tx;
	Texture* mFloorTx;
	Texture* mCanonTx;
	Texture* mCanonBaseTx;

	Sprite* mCrosshairSp;
	Sprite* mBackMenuSp;
	Sprite* mBackLv1Sp;
	Sprite* mFloorSp;
	Sprite* mCanonSp;
	Sprite* mCanonBaseSp;
	
	//Avatar
	Avatar* mFloorAvatar;
	Avatar* mCanonAvatar;

	enum GameState { MENU, LEVEL1, LEVEL2, LEVEL3, EXIT };
	GameState mState;

	float mFps, mFrameTime, mActualTime;
	bool nextLevel;


	void SetCamara(float mZoom);
	void SetImages();
	void SetMenu();
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