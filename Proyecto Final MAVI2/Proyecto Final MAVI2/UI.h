#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class UI
{
public:

	UI();
	~UI();

	bool IsPlayButtonClicked(int x, int y);
	bool IsExitButtonClicked(int x, int y);
	bool IsNextLevelButtonClicked(int x, int y);
	void SetMenu();
	void SetNewMenu();
	void SetImages(RenderWindow& mWindow);
	void DrawMenu(RenderWindow& mWindow);
	void DrawNewMenu(RenderWindow& mWindow);
	void DrawImages(RenderWindow& mWindow);

private:

	Font* mFont;
	Text* mText;
	Text* mPlayText;
	Text* mPlayNextLevelText;
	Text* mExitText;

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
};