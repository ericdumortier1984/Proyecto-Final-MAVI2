#pragma once
#include "MainHeader.h"

#define MAX_MAIN_MENU 5

class MainMenu
{
public:

	MainMenu(float width, float height);
	~MainMenu();

	void Draw(RenderWindow& mWindow);
	void MoveUp();
	void MoveDown();
	int MainMenuPressed() { return mMainMenuSelected; }

private:

	int mMainMenuSelected;
	Font* mFont;
	Text mMainMenu[MAX_MAIN_MENU];

	Texture* mBackMenuTx;
	Texture* mTitleTx;

	Sprite* mBackMenuSp;
	Sprite* mTitleSp;
};