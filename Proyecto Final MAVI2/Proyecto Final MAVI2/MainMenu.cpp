#include "MainMenu.h"

// Constructor
MainMenu::MainMenu(float mWidth, float mHeight)
{

	cout << "[MENU]" << endl; // Debug

	mFont = new Font;
	mFont->loadFromFile("Fonts/COOPBL.ttf");

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

	// Audio
	mMenuMusic = new Music;
	if (!mMenuMusic->openFromFile("Sounds/menuCircusMusic.ogg")) { cout << "Error al cargar musica de MENU" << endl; }
	mMenuMusic->setVolume(15.f);
	mMenuMusic->setLoop(false);
	mMenuMusic->play();

	// START GAME
	mMainMenu[0].setFont(*mFont);
	mMainMenu[0].setCharacterSize(50);
	mMainMenu[0].setFillColor(Color::Black);
	mMainMenu[0].setString("START GAME");
	mMainMenu[0].setOutlineColor(Color::Black);
	mMainMenu[0].setOutlineThickness(2);
	mMainMenu[0].setPosition(490, 380);
	// INFO
	mMainMenu[1].setFont(*mFont);
	mMainMenu[1].setCharacterSize(50);
	mMainMenu[1].setFillColor(Color::Black);
	mMainMenu[1].setString("INFO");
	mMainMenu[1].setOutlineColor(Color::Black);
	mMainMenu[1].setOutlineThickness(2);
	mMainMenu[1].setPosition(580, 450);
	// EXIT
	mMainMenu[2].setFont(*mFont);
	mMainMenu[2].setCharacterSize(50);
	mMainMenu[2].setFillColor(Color::Black);
	mMainMenu[2].setString("EXIT");
	mMainMenu[2].setOutlineColor(Color::Black);
	mMainMenu[2].setOutlineThickness(2);
	mMainMenu[2].setPosition(580, 520);

	// SELECT LEVEL
	mLevelSelect = new Text;
	mLevelSelect->setFont(*mFont);
	mLevelSelect->setCharacterSize(50);
	mLevelSelect->setFillColor(Color(144, 292, 144));
	mLevelSelect->setString("CHOOSE YOUR LEVEL");
	mLevelSelect->setOutlineColor(Color::Black);
	mLevelSelect->setOutlineThickness(0.5);
	mLevelSelect->setPosition(400, 150);

	//LEVEL 1 
	mLevelMenu[0].setFont(*mFont);
	mLevelMenu[0].setCharacterSize(25);
	mLevelMenu[0].setFillColor(Color(144, 292, 144));
	mLevelMenu[0].setString("LEVEL 1 (EASY)");
	mLevelMenu[0].setOutlineColor(Color::Black);
	mLevelMenu[0].setOutlineThickness(0.5);
	mLevelMenu[0].setPosition(280, 285);
	//LEVEL 2
	mLevelMenu[1].setFont(*mFont);
	mLevelMenu[1].setCharacterSize(25);
	mLevelMenu[1].setFillColor(Color(144, 292, 144));
	mLevelMenu[1].setString("LEVEL 2 (NORMAL)");
	mLevelMenu[1].setOutlineColor(Color::Black);
	mLevelMenu[1].setOutlineThickness(0.5);
	mLevelMenu[1].setPosition(540, 285);
	//LEVEL 3
	mLevelMenu[2].setFont(*mFont);
	mLevelMenu[2].setCharacterSize(25);
	mLevelMenu[2].setFillColor(Color(144, 292, 144));
	mLevelMenu[2].setString("LEVEL 3 (HARD)");
	mLevelMenu[2].setOutlineColor(Color::Black);
	mLevelMenu[2].setOutlineThickness(0.5);
	mLevelMenu[2].setPosition(830, 285);
	
	// Cargar imagenes en miniatura
	for (int i = 0; i < MAX_LEVEL_MENU; i++)
	{
		mMiniLevelTx[i] = new Texture;
		if (!mMiniLevelTx[i]->loadFromFile("Assets/Backgrounds/level" + to_string(i + 1) + ".png")) { cout << "Error al cargar imagen de nivel " << i + 1 << endl; }
		mMiniLevelSp[i] = new Sprite;
		mMiniLevelSp[i]->setTexture(*mMiniLevelTx[i]);
		mMiniLevelSp[i]->setScale(0.20f, 0.20f);
		mMiniLevelSp[i]->setPosition(250 + i * 280, 330);
	}

	// Bordes de las miniaturas
	for (int i = 0; i < MAX_LEVEL_MENU; i++)
	{
		mMiniLevelThickness[i] = new RectangleShape;
		mMiniLevelThickness[i]->setSize(Vector2f(253, 142)); 
		mMiniLevelThickness[i]->setFillColor(Color::Transparent); 
		mMiniLevelThickness[i]->setOutlineColor(Color::Black); 
		mMiniLevelThickness[i]->setOutlineThickness(2); 
		mMiniLevelThickness[i]->setPosition(250 + i * 280, 330); 
	}

	// Texto de información
	mInfoText = new Text;
	mInfoText->setFont(*mFont);
	mInfoText->setCharacterSize(30);
	mInfoText->setFillColor(Color::Yellow);
	mInfoText->setString("Este es el menu de informacion.\nPresiona ESC para volver.");
	mInfoText->setPosition(100, 100);

	mMainMenuSelected = -1;
	mLevelMenuSelected = -1;
}

// Deconstructor
MainMenu::~MainMenu()
{
	delete mFont;
	delete mLevelSelect;
	delete mBackMenuSp;
	delete mBackMenuTx;
	delete mTitleSp;
	delete mTitleTx;
	delete mInfoText;
	for (int i = 0; i < MAX_LEVEL_MENU; i++)
	{
		delete mMiniLevelTx[i];
		delete mMiniLevelSp[i];
		delete mMiniLevelThickness[i];
	}
}

// Seleccion de opciones a traves de teclado y mouse
void MainMenu::MoveUp()
{
	if (mMainMenuSelected - 1 >= 0)
	{
		mMainMenu[mMainMenuSelected].setFillColor(Color::Black);
		mMainMenuSelected--;
		mMainMenu[mMainMenuSelected].setFillColor(Color(230, 230, 250));
	}
}

void MainMenu::MoveDown()
{
	if (mMainMenuSelected + 1 < MAX_MAIN_MENU)
	{
		mMainMenu[mMainMenuSelected].setFillColor(Color::Black);
		mMainMenuSelected++;
		mMainMenu[mMainMenuSelected].setFillColor(Color(230, 230, 250));
	}
}

void MainMenu::MouseMove(Vector2f mousePos)
{
	for (int i = 0; i < MAX_LEVEL_MENU; i++)
	{
		if (mMiniLevelSp[i]->getGlobalBounds().contains(mousePos))
		{
			mLevelMenuSelected = i;
			break;
		}
	}
}

// Audio
void MainMenu::PlayMusic()
{

	mMenuMusic->play();
}

void MainMenu::StopMusic()
{

	mMenuMusic->stop();
}

// Dibujamos menu principal
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

// Dibujamos menu de niveles
void MainMenu::DrawLevelMenu(RenderWindow& mWindow)
{

	mWindow.setMouseCursorVisible(true);
	mMenuMusic->stop();
	mWindow.clear(Color(230, 230, 250));

	mWindow.draw(*mLevelSelect);

	for (int i = 0; i < MAX_LEVEL_MENU; i++)
	{
		mWindow.draw(mLevelMenu[i]);
		mWindow.draw(*mMiniLevelSp[i]);
		mWindow.draw(*mMiniLevelThickness[i]);
	}
}

// Dibujamos menu de informacion
void MainMenu::DrawInfo(RenderWindow& mWindow)
{

	mWindow.setMouseCursorVisible(false);
	mWindow.clear();
	mWindow.draw(*mInfoText);
}