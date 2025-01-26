#include "UI.h"

UI::UI()
{

	mFont = new Font;
	if (!mFont->loadFromFile("Fonts/ARLRDBD.ttf")) { cout << "Error al cargar la fuente" << endl; }

	SetMenu();
}

UI::~UI()
{

	delete mFont;
	delete mPlayText;
	delete mExitText;
	delete mCrosshairTx;
	delete mBackMenuTx;
	delete mTitleTx;
	delete mButtonPlayTx;
	delete mButtonExitTx;
	delete mCrosshairSp;
	delete mBackMenuSp;
	delete mTitleSp;
	delete mButtonPlaySp;
	delete mButtonExitSp;
}

bool UI::IsPlayButtonClicked(int x, int y)
{
	return mButtonPlaySp->getGlobalBounds().contains(x, y);
}

bool UI::IsExitButtonClicked(int x, int y)
{
	return mButtonExitSp->getGlobalBounds().contains(x, y);
}

void UI::SetMenu()
{

	cout << "[MENU]" << endl; // Debug
	mBackMenuTx = new Texture;
	if (!mBackMenuTx->loadFromFile("Assets/Backgrounds/backgroundMain2.jpg")) { cout << "Error al cargar imagen de fondo en menu" << endl; }
	mBackMenuSp = new Sprite;
	mBackMenuSp->setTexture(*mBackMenuTx);
	mBackMenuSp->setScale(1280.f / mBackMenuTx->getSize().x, 720.f / mBackMenuTx->getSize().y);

	mButtonPlayTx = new Texture;
	if (!mButtonPlayTx->loadFromFile("Assets/Backgrounds/playButton.png")) { cout << "Error al cargar imagen de boton play" << endl; }
	mButtonPlaySp = new Sprite;
	mButtonPlaySp->setTexture(*mButtonPlayTx);
	mButtonPlaySp->setScale(0.20f, 0.20f);
	mButtonPlaySp->setPosition(580.f, 380.f);

	mPlayText = new Text;
	mPlayText->setFont(*mFont);
	mPlayText->setFillColor(Color::White);
	mPlayText->setOutlineColor(Color::Black);
	mPlayText->setOutlineThickness(5.f);
	mPlayText->setCharacterSize(40);
	mPlayText->setPosition(260.f, 420.f);
	mPlayText->setString("PLAY GAME ->");

	mButtonExitTx = new Texture;
	if (!mButtonExitTx->loadFromFile("Assets/Backgrounds/exitButton.png")) { cout << "Error al cargar imagen de boton exit" << endl; }
	mButtonExitSp = new Sprite;
	mButtonExitSp->setTexture(*mButtonExitTx);
	mButtonExitSp->setScale(0.25f, 0.25f);
	mButtonExitSp->setPosition(580.f, 550.f);

	mExitText = new Text;
	mExitText->setFont(*mFont);
	mExitText->setFillColor(Color::White);
	mExitText->setOutlineColor(Color::Black);
	mExitText->setOutlineThickness(5.f);
	mExitText->setCharacterSize(40);
	mExitText->setPosition(270.f, 580.f);
	mExitText->setString("EXIT GAME ->");

	mTitleTx = new Texture;
	if (!mTitleTx->loadFromFile("Assets/Backgrounds/title.png")) { cout << "Error al cargar imagen de titulo" << endl; }
	mTitleSp = new Sprite;
	mTitleSp->setTexture(*mTitleTx);
	mTitleSp->setScale(1.25f, 0.75f);
	mTitleSp->setPosition(200.f, 0.f);
}

void UI::SetImages(RenderWindow& mWindow)
{
	mCrosshairTx = new Texture;

	if (!mCrosshairTx->loadFromFile("Assets/Objects/crosshair.png")) { cout << "Error al cargar la textura de crosshair" << endl; }

	mCrosshairSp = new Sprite;

	//Crosshair
	mCrosshairSp->setTexture(*mCrosshairTx);
	mCrosshairSp->setScale(0.10f, 0.10f);
	mCrosshairSp->setOrigin(mCrosshairTx->getSize().x / 2, mCrosshairTx->getSize().y / 2);
	mCrosshairSp->setPosition(mWindow.mapPixelToCoords(Mouse::getPosition(mWindow)));
}

void UI::DrawMenu(RenderWindow& mWindow)
{

	mWindow.setMouseCursorVisible(true);
	mWindow.draw(*mBackMenuSp);
	mWindow.draw(*mTitleSp);
	mWindow.draw(*mButtonPlaySp);
	mWindow.draw(*mButtonExitSp);
	mWindow.draw(*mPlayText);
	mWindow.draw(*mExitText);
}

void UI::DrawImages(RenderWindow& mWindow)
{

	mWindow.draw(*mCrosshairSp);
}