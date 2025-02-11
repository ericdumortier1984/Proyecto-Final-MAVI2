#include "MainMenu.h"

// Constructor
MainMenu::MainMenu(float mWidth, float mHeight)
{

	cout << "[MENU]" << endl; // Debug

	// Carga de la fuente
	mFont = new Font;
	mFont->loadFromFile("Fonts/COOPBL.ttf");

	// Carga de la textura y sprite de fondo y titulo
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
	mTitleSp->setPosition(290.f, 0.f);

	// Carga de la musica del menu
	mMenuMusic = new Music;
	if (!mMenuMusic->openFromFile("Sounds/menuCircusMusic.ogg")) { cout << "Error al cargar musica de MENU" << endl; }
	mMenuMusic->setVolume(15.f);
	mMenuMusic->setLoop(false);
	mMenuMusic->play();

	///////////////// Fuentes de los Botones ////////////////
	
	// boton START GAME
	mMainMenu[0].setFont(*mFont);
	mMainMenu[0].setCharacterSize(50);
	mMainMenu[0].setFillColor(Color::Black);
	mMainMenu[0].setString("START GAME");
	mMainMenu[0].setOutlineColor(Color::Black);
	mMainMenu[0].setOutlineThickness(2);
	mMainMenu[0].setPosition(490.f, 380.f);
	// Boton INFO
	mMainMenu[1].setFont(*mFont);
	mMainMenu[1].setCharacterSize(50);
	mMainMenu[1].setFillColor(Color::Black);
	mMainMenu[1].setString("INFO");
	mMainMenu[1].setOutlineColor(Color::Black);
	mMainMenu[1].setOutlineThickness(2);
	mMainMenu[1].setPosition(580.f, 450.f);
	// Boton EXIT
	mMainMenu[2].setFont(*mFont);
	mMainMenu[2].setCharacterSize(50);
	mMainMenu[2].setFillColor(Color::Black);
	mMainMenu[2].setString("EXIT");
	mMainMenu[2].setOutlineColor(Color::Black);
	mMainMenu[2].setOutlineThickness(2);
	mMainMenu[2].setPosition(580.f, 520.f);

	// Texto SELECT LEVEL
	mLevelSelect = new Text;
	mLevelSelect->setFont(*mFont);
	mLevelSelect->setCharacterSize(50);
	mLevelSelect->setFillColor(Color(255, 0, 144)); // 144,292, 144
	mLevelSelect->setString("CHOOSE YOUR LEVEL");
	mLevelSelect->setOutlineColor(Color::Black);
	mLevelSelect->setOutlineThickness(0.5);
	mLevelSelect->setPosition(390.f, 140.f);

	// Boton LEVEL 1 
	mLevelMenu[0].setFont(*mFont);
	mLevelMenu[0].setCharacterSize(25);
	mLevelMenu[0].setFillColor(Color(255, 0, 144));
	mLevelMenu[0].setString("                  LEVEL 1\n\n\n\n\n\n\nGET THE RING OF FIRE");
	mLevelMenu[0].setOutlineColor(Color::Black);
	mLevelMenu[0].setOutlineThickness(0.5);
	mLevelMenu[0].setPosition(150.f, 285.f);
	// Boton LEVEL 2
	mLevelMenu[1].setFont(*mFont);
	mLevelMenu[1].setCharacterSize(25);
	mLevelMenu[1].setFillColor(Color(255, 0, 144));
	mLevelMenu[1].setString("                LEVEL 2\n\n\n\n\n\n\n    GET THE BALLONS");
	mLevelMenu[1].setOutlineColor(Color::Black);
	mLevelMenu[1].setOutlineThickness(0.5);
	mLevelMenu[1].setPosition(490.f, 285.f);
	// Boton LEVEL 3
	mLevelMenu[2].setFont(*mFont);
	mLevelMenu[2].setCharacterSize(25);
	mLevelMenu[2].setFillColor(Color(255, 0, 144));
	mLevelMenu[2].setString("                 LEVEL 3\n\n\n\n\n\n\nGET THE STACK OF CANS\n   AND DO NOT TOUCH\n   THE SPIKED WHEELS");
	mLevelMenu[2].setOutlineColor(Color::Black);
	mLevelMenu[2].setOutlineThickness(0.5);
	mLevelMenu[2].setPosition(810, 285);
	
	// Cargar imagenes en miniatura
	for (int i = 0; i < MAX_LEVEL_MENU; i++)
	{
		mMiniLevelTx[i] = new Texture;
		if (!mMiniLevelTx[i]->loadFromFile("Assets/Backgrounds/level" + to_string(i + 1) + ".png")) { cout << "Error al cargar imagen de nivel " << i + 1 << endl; }
		mMiniLevelSp[i] = new Sprite;
		mMiniLevelSp[i]->setTexture(*mMiniLevelTx[i]);
		mMiniLevelSp[i]->setScale(0.20f, 0.20f);
		mMiniLevelSp[i]->setPosition(180 + i * 330, 330);
	}

	// Bordes de las miniaturas
	for (int i = 0; i < MAX_LEVEL_MENU; i++)
	{
		mMiniLevelThickness[i] = new RectangleShape;
		mMiniLevelThickness[i]->setSize(Vector2f(253, 142)); 
		mMiniLevelThickness[i]->setFillColor(Color::Transparent); 
		mMiniLevelThickness[i]->setOutlineColor(Color::Black); 
		mMiniLevelThickness[i]->setOutlineThickness(2); 
		mMiniLevelThickness[i]->setPosition(180 + i * 330, 330); 
	}

	// Menu INFO
	mInfoText = new Text;
	mInfoText->setFont(*mFont);
	mInfoText->setCharacterSize(30);
	mInfoText->setFillColor(Color::Red);
	mInfoText->setOutlineThickness(0.5);
	mInfoText->setOutlineColor(Color::Black);
	mInfoText->setString("PRESS ESC TO RETURN");
	mInfoText->setPosition(100, 25);

	mKeyboardTx = new Texture;
	if (!mKeyboardTx->loadFromFile("Assets/Backgrounds/keyboard.jpg")) { cout << "Error al cargar imagen de teclado" << endl; }
	mKeyboardSp = new Sprite;
	mKeyboardSp->setTexture(*mKeyboardTx);
	mKeyboardSp->setScale(0.025f, 0.025f);
	mKeyboardSp->setPosition(100.f, 100.f);

	mMouseTx = new Texture;
	if (!mMouseTx->loadFromFile("Assets/Backgrounds/mouse.png")) { cout << "Error al cargar imagen de mouse" << endl; }
	mMouseSp = new Sprite;
	mMouseSp->setTexture(*mMouseTx);
	mMouseSp->setScale(0.15f, 0.15f);
	mMouseSp->setPosition(150.f, 200.f);

	mLevelInfoTx = new Texture;
	if (!mLevelInfoTx->loadFromFile("Assets/Backgrounds/levelInfo.png")) { cout << "Error al cargar imagen de info de nivel" << endl; }
	mLevelInfoSp = new Sprite;
	mLevelInfoSp->setTexture(*mLevelInfoTx);
	mLevelInfoSp->setScale(0.55f, 0.55f);
	mLevelInfoSp->setPosition(150.f, 350.f);

	mKeyboardText = new Text;
	mKeyboardText->setFont(*mFont);
	mKeyboardText->setCharacterSize(20);
	mKeyboardText->setFillColor(Color::Magenta);
	mKeyboardText->setOutlineThickness(0.5);
	mKeyboardText->setOutlineColor(Color::Black);
	mKeyboardText->setString("USE KEY UP AND DOWN TO SELECT IN MAIN MENU");
	mKeyboardText->setPosition(300.f, 125.f);

	mMouseText = new Text;
	mMouseText->setFont(*mFont);
	mMouseText->setCharacterSize(20);
	mMouseText->setFillColor(Color::Magenta);
	mMouseText->setOutlineThickness(0.5);
	mMouseText->setOutlineColor(Color::Black);
	mMouseText->setString("USE MOUSE LEFT BUTTON TO SELECT LEVEL \nUSE MOUSE LEFT BUTTON TO SHOOT RAGDOLL\nMOVE MOUSE TO ROTATE DE CANON");
	mMouseText->setPosition(300.f, 215.f);


	// Variables que indican que inicialmente no hay nada seleccionado
	mMainMenuSelected = -1;
	mLevelMenuSelected = -1;
}

// Destructor
MainMenu::~MainMenu()
{
	delete mFont;
	delete mLevelSelect;
	delete mBackMenuSp;
	delete mBackMenuTx;
	delete mTitleSp;
	delete mTitleTx;
	delete mInfoText;
	delete mKeyboardText;
	delete mMouseText;
	delete mKeyboardTx;
	delete mKeyboardSp;
	delete mMouseTx;
	delete mMouseSp;
	delete mLevelInfoTx;
	delete mLevelInfoSp;
	for (int i = 0; i < MAX_LEVEL_MENU; i++)
	{
		delete mMiniLevelTx[i];
		delete mMiniLevelSp[i];
		delete mMiniLevelThickness[i];
	}
}

// Metodo para mover la seleccion de opciones hacia arriba
void MainMenu::MoveUp()
{
	if (mMainMenuSelected - 1 >= 0)
	{
		mMainMenu[mMainMenuSelected].setFillColor(Color::Black);
		mMainMenuSelected--;
		mMainMenu[mMainMenuSelected].setFillColor(Color(230, 230, 250));
	}
}

// metodo para mover la seleccion de opciones hacia abajo
void MainMenu::MoveDown()
{
	if (mMainMenuSelected + 1 < MAX_MAIN_MENU)
	{
		mMainMenu[mMainMenuSelected].setFillColor(Color::Black);
		mMainMenuSelected++;
		mMainMenu[mMainMenuSelected].setFillColor(Color(230, 230, 250));
	}
}

// Metodo para manejar el movimiento del mouse
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

// Metodo para reproducir la musica del menu
void MainMenu::PlayMusic()
{

	mMenuMusic->play();
}

// metodo para detener la musica del menu
void MainMenu::StopMusic()
{

	mMenuMusic->stop();
}

// Metodo para dibujar el menu principal
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

// Metodo para dibujar el menu de niveles
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

// Metodo para dibujar el menu de informacion
void MainMenu::DrawInfo(RenderWindow& mWindow)
{

	mWindow.setMouseCursorVisible(false);
	mWindow.clear(Color(230, 230, 250));
	mWindow.draw(*mInfoText);
	mWindow.draw(*mKeyboardText);
	mWindow.draw(*mMouseText);
	mWindow.draw(*mKeyboardSp);
	mWindow.draw(*mMouseSp);
	mWindow.draw(*mLevelInfoSp);
}