#pragma once
#include<box2d/box2d.h>
#include<SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

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

	RenderWindow mWindow;
	Font mFont;
	Text mTitle;
	Text mPlay;
	Text mExit;
	Clock mClock;

	enum GameState { MENU, LEVEL1, LEVEL2, LEVEL3, EXIT };
	GameState mState;
};