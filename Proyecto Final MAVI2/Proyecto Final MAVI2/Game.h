#include "Avatar.h"
#include "Ragdoll.h"

class Game
{
public:

	Game();
	~Game();

	void SetCamara(float mZoom);
	void SetImages();
	void InitPhysics();
	void UpdatePhysics();
	void Run();
	void ProcessEvents();
	void Update();
	void DrawMenu();
	void RunLevel();
	void Draw();
	
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
	Texture* mBackLv1Tx;
	Texture* mFloorTx;
	Texture* mCanonTx;
	Texture* mCanonFootTx;

	Sprite* mBackLv1Sp;
	Sprite* mFloorSp;
	Sprite* mCanonSp;
	Sprite* mCanonFootSp;
	
	//Avatar
	Avatar* floorAvatar;
	Avatar* canonAvatar;

	enum GameState { MENU, LEVEL1, LEVEL2, LEVEL3, EXIT };
	GameState mState;

	float mFps, mFrameTime, mActualTime;
};