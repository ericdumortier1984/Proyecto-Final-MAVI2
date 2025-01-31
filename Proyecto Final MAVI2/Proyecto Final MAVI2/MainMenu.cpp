#include "MainMenu.h"

MainMenu::MainMenu(float mWidth, float mHeight)
{

	cout << "[MENU]" << endl; // Debug

	mFont = new Font;
	mFont->loadFromFile("Fonts/ARLRDBD.ttf");

	mBackMenuTx = new Texture;
	if (!mBackMenuTx->loadFromFile("Assets/Backgrounds/backgroundMain2.jpg")) { cout << "Error al cargar imagen de fondo en menu" << endl; }
	mBackMenuSp = new Sprite;
	mBackMenuSp->setTexture(*mBackMenuTx);
	mBackMenuSp->setScale(1280.f / mBackMenuTx->getSize().x, 720.f / mBackMenuTx->getSize().y);

	mTitleTx = new Texture;
	if (!mTitleTx->loadFromFile("Assets/Backgrounds/title.png")) { cout << "Error al cargar imagen de titulo" << endl; }
	mTitleSp = new Sprite;
	mTitleSp->setTexture(*mTitleTx);
	mTitleSp->setScale(1.f, 0.5f);
	mTitleSp->setPosition(mWidth / 4, 0.f);

	//Mision 1 
	mMainMenu[0].setFont(*mFont);
	mMainMenu[0].setCharacterSize(50);
	mMainMenu[0].setFillColor(Color::Black);
	mMainMenu[0].setString("MISSION 1 (EASY)");
	mMainMenu[0].setPosition(400, 330);
	//Mision 2
	mMainMenu[1].setFont(*mFont);
	mMainMenu[1].setCharacterSize(50);
	mMainMenu[1].setFillColor(Color::Black);
	mMainMenu[1].setString("MISSION 2 (NORMAL)");
	mMainMenu[1].setPosition(400, 380);
	//Mision 3
	mMainMenu[2].setFont(*mFont);
	mMainMenu[2].setCharacterSize(50);
	mMainMenu[2].setFillColor(Color::Black);
	mMainMenu[2].setString("MISSION 3 (HARD)");
	mMainMenu[2].setPosition(400, 430);
	//INFORMACION SOBRE EL JUEGO
	mMainMenu[3].setFont(*mFont);
	mMainMenu[3].setCharacterSize(50);
	mMainMenu[3].setFillColor(Color::Black);
	mMainMenu[3].setString("INFO");
	mMainMenu[3].setPosition(400, 480);
	//SALIDA DEL JUEGO
	mMainMenu[4].setFont(*mFont);
	mMainMenu[4].setCharacterSize(50);
	mMainMenu[4].setFillColor(Color::Black);
	mMainMenu[4].setString("EXIT");
	mMainMenu[4].setPosition(400, 530);

	mMainMenuSelected = -1;
}

MainMenu::~MainMenu()
{
	delete mFont;
	delete mBackMenuSp;
	delete mBackMenuTx;
	delete mTitleSp;
	delete mTitleTx;
}

void MainMenu::Draw(RenderWindow& mWindow)
{

	mWindow.setMouseCursorVisible(false);
	mWindow.draw(*mBackMenuSp);
	mWindow.draw(*mTitleSp);

	for (int i = 0; i < MAX_MAIN_MENU; i++)
	{
		mWindow.draw(mMainMenu[i]);
	}
}

void MainMenu::MoveUp()
{
	if (mMainMenuSelected - 1 >= 0)
	{
		mMainMenu[mMainMenuSelected].setFillColor(Color::Black);
		mMainMenuSelected--;
		if (mMainMenuSelected == -1)
		{
			mMainMenuSelected == 2;
		}
		mMainMenu[mMainMenuSelected].setFillColor(Color::Red);
	}
}

void MainMenu::MoveDown()
{
	if (mMainMenuSelected + 1 <= MAX_MAIN_MENU)
	{
		mMainMenu[mMainMenuSelected].setFillColor(Color::Black);
		mMainMenuSelected++;
		if (mMainMenuSelected == 5)
		{
			mMainMenuSelected == 0;
		}
		mMainMenu[mMainMenuSelected].setFillColor(Color::Red);
	}
}