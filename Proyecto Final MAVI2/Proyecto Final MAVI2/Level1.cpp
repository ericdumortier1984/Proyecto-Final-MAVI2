#include "Level1.h"

// Constructor
Level1::Level1(int mWidth, int mHeight, bool mUnlocked) : Level(mWidth, mHeight, mUnlocked), mUnlocked(mUnlocked)
{

	cout << "[LEVEL 1]" << endl; // Debug

	// Inicializacion del listener de colisiones
	mContactListener = new ContactListener(this);

	// configuracion de colisiones
	CheckCollisions();

	// Inicializacion pendulos
	if (mPendulum[0] == nullptr) mPendulum[0] = new Pendulum(*mWorld, { -45.f, 128.f });
	if (mPendulum[1] == nullptr) mPendulum[1] = new Pendulum(*mWorld, { 15.f, 120.f });
	if (mPendulum[2] == nullptr) mPendulum[2] = new Pendulum(*mWorld, { 70.f, 120.f });

	// Inicializacion cajas dinamicas
	if (mBox[0] == nullptr) mBox[0] = new Box(*mWorld, { 80.f, 120.5f });
	if (mBox[1] == nullptr) mBox[1] = new Box(*mWorld, { 80.f, 130.5f });
	if (mBox[2] == nullptr) mBox[2] = new Box(*mWorld, { 80.f, 140.5f });
	if (mBox[3] == nullptr) mBox[3] = new Box(*mWorld, { 25.f, 120.5f });
	if (mBox[4] == nullptr) mBox[4] = new Box(*mWorld, { 25.f, 130.5f });
	if (mBox[5] == nullptr) mBox[5] = new Box(*mWorld, { 25.f, 140.5f });
	if (mBox[6] == nullptr) mBox[6] = new Box(*mWorld, { -30.f, 120.5f });
	if (mBox[7] == nullptr) mBox[7] = new Box(*mWorld, { -30.f, 130.5f });
	if (mBox[8] == nullptr) mBox[8] = new Box(*mWorld, { -30.f, 140.5f });

	// Inicializacion de cajas estaticas
	if (mStaticBox[0] == nullptr) mStaticBox[0] = new StaticBox(*mWorld, { -30.f, 159.5f });
	if (mStaticBox[1] == nullptr) mStaticBox[1] = new StaticBox(*mWorld, { 25.f, 159.5f });
	if (mStaticBox[2] == nullptr) mStaticBox[2] = new StaticBox(*mWorld, { 80.f, 159.5f });
	
	// Inicializacion aro de fuego
	if (mCircleOfFire == nullptr) mCircleOfFire = new CircleOfFire(*mWorld, { 120.f, 140.5f });
}

// Destructor
Level1::~Level1()
{
	for (int i = 0; i < 10; ++i)
	{
		delete mPendulum[i];
		delete mBox[i];
		delete mStaticBox[i];
	}
	delete mCircleOfFire;
}

// Metodo para configurar las colisiones
void Level1::CheckCollisions()
{

	mWorld->SetContactListener(mContactListener);
}

// Metodo para verificar si el nivel esta desbloqueado
bool Level1::UnlockedLevel() const
{
	return mUnlocked;
}

// metodo para finalizar el nivel
bool Level1::FinishLevel()
{
	if (!mLevelFinish)
	{
		mLevelFinish = true;
		mLevelMusic->stop();
		mVictorySound->play();
		mStateMsg->setPosition(-20.f, 55.f);
		ShowMsg("LEVEL WIN");
	}
	return true;
}

// Metodo para ejecutar el nivel
void Level1::RunLevel()
{

	// Limpiar pantalla
	mWindow->clear(Color(173, 216, 230)); // LightBlue
	
	// Acercamos la camara
	SetCamara(0.20f);

	// Ocultar cursor del mouse
	mWindow->setMouseCursorVisible(false);

	// Dibujar
	mFloor->Draw(*mWindow); // Piso
	mCanon->Draw(*mWindow); // Canon
	for (int i = 0; i < 3; i++) { if (mPendulum[i] != nullptr) mPendulum[i]->Draw(*mWindow); } // Pendulos
	for (int i = 0; i < 3; ++i) { if (mStaticBox[i] != nullptr) mStaticBox[i]->Draw(*mWindow); } // Cajas estaticas
	for (int i = 0; i < 9; ++i) { if (mBox[i] != nullptr) mBox[i]->Draw(*mWindow); } // Cajas dinamicas
	if (mCircleOfFire != nullptr) { mCircleOfFire->Draw(*mWindow); } // Aro de fuego
	if (mRagdoll != nullptr) { mRagdoll->Draw(*mWindow); } // Ragdoll
	for (int i = 0; i < 3; i++) { mWindow->draw(*mUIsp[i]); } // Fondo de marcadores UI
	mWindow->draw(*mCountdownTimer); // Contador de tiempo
	mWindow->draw(*mRagdollCounter); // Contador de ragdolls
	mWindow->draw(*mCanonPower); // Marcador de potencia de disparo
	mWindow->draw(*mCrosshairSp); // Crosshair

	//Mostrar
	mWindow->display();
}
