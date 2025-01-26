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
	void SetMenu();
	void SetImages(RenderWindow& mWindow);
	void DrawMenu(RenderWindow& mWindow);
	void DrawImages(RenderWindow& mWindow);

private:

	Font* mFont;
	Text* mText;
	Text* mPlayText;
	Text* mExitText;

	Texture* mCrosshairTx;
	Texture* mBackMenuTx;
	Texture* mTitleTx;
	Texture* mButtonPlayTx;
	Texture* mButtonExitTx;

	Sprite* mCrosshairSp;
	Sprite* mBackMenuSp;
	Sprite* mTitleSp;
	Sprite* mButtonPlaySp;
	Sprite* mButtonExitSp;
};