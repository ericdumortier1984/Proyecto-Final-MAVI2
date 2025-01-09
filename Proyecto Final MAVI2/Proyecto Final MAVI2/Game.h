#include "Avatar.h"
#include "Ragdoll.h"

class Game
{
public:

	Game();
	~Game();

	void SetCamara(float mZoom);
	void InitPhysics();
	void UpdatePhysics();
	void Run();
	void ProcessEvents();
	void Update();
	void DrawMenu();
	void RunLevel(Color color);
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
	
	enum GameState { MENU, LEVEL1, LEVEL2, LEVEL3, EXIT };
	GameState mState;

	float mFps, mFrameTime, mActualTime;
};