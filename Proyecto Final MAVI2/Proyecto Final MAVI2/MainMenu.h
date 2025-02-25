#pragma once
#include "MainHeader.h"

#define MAX_MAIN_MENU 3
#define MAX_LEVEL_MENU 3

class MainMenu
{
public:

	// Constructor y deconstructor
	MainMenu(float width, float height);
	~MainMenu();

	// Menu principal
	void Draw(RenderWindow& mWindow);
	void PlayMusic();
    void StopMusic();
	void MoveUp();
	void MoveDown();
	int MainMenuPressed() { return mMainMenuSelected; }

	// Menu informacion
	void DrawInfo(RenderWindow& mWindow);


	// Menu seleccion de niveles
	void DrawLevelMenu(RenderWindow& mWindow);
	void MouseMove(Vector2f mMousePos);
	int LevelMenuPressed() { return mLevelMenuSelected; }

private:

	// variables que son retornadas en metodo ...Pressed()
	int mMainMenuSelected;
	int mLevelMenuSelected;

	// Audio
	Music* mMenuMusic;

	// Fuentes y textos
	Font* mFont;
	Text mMainMenu[MAX_MAIN_MENU];
	Text mLevelMenu[MAX_LEVEL_MENU];
	Text* mLevelSelect;
	Text* mInfoText;
	Text* mKeyboardText;
	Text* mMouseText;

	// Texturas, sprites y shapes
	Texture* mBackMenuTx;
	Texture* mTitleTx;
	Texture* mMiniLevelTx[MAX_LEVEL_MENU];
	Texture* mKeyboardTx;
	Texture* mMouseTx;
	Texture* mLevelInfoTx;

	Sprite* mBackMenuSp;
	Sprite* mTitleSp;
	Sprite* mMiniLevelSp[MAX_LEVEL_MENU];
	Sprite* mKeyboardSp;
	Sprite* mMouseSp;
	Sprite* mLevelInfoSp;
	
	RectangleShape* mMiniLevelThickness[MAX_LEVEL_MENU];
};