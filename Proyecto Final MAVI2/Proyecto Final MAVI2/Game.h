#include "Avatar.h"
#include "Ragdoll.h"

class Game
{
public:

	Game();
	~Game();

	void Run();
	void ProcessEvents();
	void Update();
	void DrawMenu();
	void RunLevel(Color color);
	void Draw();
	
private:

	RenderWindow* mWindow;
	Font* mFont;
	Text* mTitle;
	Text* mPlay;
	Text* mExit;
	Clock* mClock;

	enum GameState { MENU, LEVEL1, LEVEL2, LEVEL3, EXIT };
	GameState mState;
};