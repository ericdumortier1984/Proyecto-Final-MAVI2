#include "Level2.h"

// Constructor
Level2::Level2(int mWidth, int mHeight, bool mUnlocked) : Level(mWidth, mHeight, mUnlocked), mUnlocked(mUnlocked)
{

	cout << "[LEVEL 2]" << endl; // Debug

	// Inicialización del listener de colisiones
	mContactListener = new ContactListener(this);

	// Configuración de colisiones
	CheckCollisions();

	// Poleas
	if (mPulley[0] == nullptr) mPulley[0] = new Pulley(*mWorld, { -25.f, 90.f });
	if (mPulley[1] == nullptr) mPulley[1] = new Pulley(*mWorld, { 80.f, 70.f });
	
	// Cajas dinamicas
	if (mBox[0] == nullptr) mBox[0] = new Box(*mWorld,   { -40.f, 110.5f });
	if (mBox[1] == nullptr) mBox[1] = new Box(*mWorld,   { -39.f, 120.5f });
	if (mBox[2] == nullptr) mBox[2] = new Box(*mWorld,   { -39.f, 130.5f });
	if (mBox[3] == nullptr) mBox[3] = new Box(*mWorld,   { 20.f, 120.5f });
	if (mBox[4] == nullptr) mBox[4] = new Box(*mWorld,   { 20.f, 130.5f });
	if (mBox[5] == nullptr) mBox[5] = new Box(*mWorld,   { 20.f, 140.5f });
	if (mBox[6] == nullptr) mBox[6] = new Box(*mWorld,   { 40.f, 120.5f });
	if (mBox[7] == nullptr) mBox[7] = new Box(*mWorld,   { 40.f, 130.5f });
	if (mBox[8] == nullptr) mBox[8] = new Box(*mWorld,   { 40.f, 140.5f });
	if (mBox[9] == nullptr) mBox[9] = new Box(*mWorld,   { 20.f, 85.5f });
	if (mBox[10] == nullptr) mBox[10] = new Box(*mWorld, { 20.f, 95.5f });
	if (mBox[11] == nullptr) mBox[11] = new Box(*mWorld, { 20.f, 105.5f });
	if (mBox[12] == nullptr) mBox[12] = new Box(*mWorld, { 40.f, 85.5f });
	if (mBox[13] == nullptr) mBox[13] = new Box(*mWorld, { 40.f, 95.5f });
	if (mBox[14] == nullptr) mBox[14] = new Box(*mWorld, { 40.f, 105.5f });
	if (mBox[15] == nullptr) mBox[15] = new Box(*mWorld, { 65.f, 95.5f });
	if (mBox[16] == nullptr) mBox[16] = new Box(*mWorld, { 65.f, 100.5f });
	if (mBox[17] == nullptr) mBox[17] = new Box(*mWorld, { 65.f, 110.5f });

	// Cajas estaticas
	if (mStaticBox[0] == nullptr) mStaticBox[0] = new StaticBox(*mWorld,{ 20.f, 160.f });
	if (mStaticBox[1] == nullptr) mStaticBox[1] = new StaticBox(*mWorld, { 20.f, 150.f });
	if (mStaticBox[2] == nullptr) mStaticBox[2] = new StaticBox(*mWorld, { 40.f, 160.f });
	if (mStaticBox[3] == nullptr) mStaticBox[3] = new StaticBox(*mWorld, { 40.f, 150.f });

	// Plataformas dinamicas
	if (mDynamicPlatform[0] == nullptr) mDynamicPlatform[0] = new DynamicPlatform(*mWorld, { 30.f, 145.f },  { 25.f, 5.f }, 0.f);
	if (mDynamicPlatform[1] == nullptr) mDynamicPlatform[1] = new DynamicPlatform(*mWorld, { 30.f, 115.f },  { 25.f, 5.f }, 0.f);
	if (mDynamicPlatform[2] == nullptr) mDynamicPlatform[2] = new DynamicPlatform(*mWorld, { 30.f, 80.f },   { 25.f, 5.f }, 0.f);
	
	// Globos
	if (mBalloons == nullptr) mBalloons = new Balloons(*mWorld, { 120.f, 150.f });
}

// Destructor
Level2::~Level2()
{
	for (int i = 0; i < 10; ++i)
	{
		delete mPulley[i];
		delete mStaticBox[i];
		delete mDynamicPlatform[i];
	}
	for (int i = 0; i < 20; i++) { delete mBox[i]; }
	delete mBalloons;
}

// Configuración de colisiones
void Level2::CheckCollisions()
{

	mWorld->SetContactListener(mContactListener);
}

// Método para verificar si el nivel está desbloqueado
bool Level2::UnlockedLevel() const
{
	return mUnlocked;
}

// Método para finalizar el nivel
bool Level2::FinishLevel()
{
	if (!mLevelFinish)
	{
		mLevelFinish = true;
		mLevelMusic->stop();
		mVictorySound->play();
		mStateMsg->setPosition(3.f, 65.f);
		ShowMsg("LEVEL WIN");
	}
	return true;
}

// Método para ejecutar el nivel
void Level2::RunLevel()
{

	// Limpiar pantalla
	mWindow->clear(Color(255, 182, 193)); // LightPink
	
	// Acercar camara
	SetCamara(0.20f);

	// Desactivar cursor del mouse
	mWindow->setMouseCursorVisible(false);

	// Actualizar globos
	float mDeltaTime = mClock->getElapsedTime().asSeconds();
	mBalloons->Update(mDeltaTime);

	// Dibujar
	mFloor->Draw(*mWindow); // Piso
	mCanon->Draw(*mWindow); // Canon
	for (int i = 0; i < 2; i++) { if (mPulley[i] != nullptr) mPulley[i]->Draw(*mWindow); } // Sistemas de poleas
	for (int i = 0; i < 18; i++) { if (mBox[i] != nullptr) mBox[i]->Draw(*mWindow); } // Cajas dinamicas
	for (int i = 0; i < 6; i++) { if (mStaticBox[i] != nullptr) mStaticBox[i]->Draw(*mWindow); } // Cajas estaticas
	if (mBalloons != nullptr) { mBalloons->Draw(*mWindow); }; // Globos
	if (mRagdoll != nullptr) { mRagdoll->Draw(*mWindow); } // Ragdoll
	for (int i = 0; i < 3; i++) { if (mDynamicPlatform[i] != nullptr) mDynamicPlatform[i]->Draw(*mWindow); } // Plataformas dinamicas
	for (int i = 0; i < 3; i++) { mWindow->draw(*mUIsp[i]); } // Interfaz UI
	mWindow->draw(*mCountdownTimer); // Cronometro
	mWindow->draw(*mRagdollCounter); // Contador de ragdolls
	mWindow->draw(*mCanonPower); // Potencia de disparo
	mWindow->draw(*mCrosshairSp); // Crosshair

	// Mostrar
	mWindow->display();
}
