#include "Level3.h"

Level3::Level3(int mWidth, int mHeight, bool mUnlocked) : Level(mWidth, mHeight, mUnlocked), mUnlocked(mUnlocked), mGetHurt(false)
{

	cout << "[LEVEL 3]" << endl; // Debug

	// Inicialiacion del listener de colisiones
	mContactListener = new ContactListener(this);

	// Configuracion de las colisiones
	CheckCollisions();

	// Inicializacion de ruedas
	if (mWheel[0] == nullptr) mWheel[0] = new Wheel(*mWorld, { 100.f, 140.f }, 5.0f, 10.f, 20.f);
	if (mWheel[1] == nullptr) mWheel[1] = new Wheel(*mWorld, { -35.f, 160.f }, 4.0f, 10.f, 20.f);
	if (mWheel[2] == nullptr) mWheel[2] = new Wheel(*mWorld, { -25.f, 160.f }, 4.0f, 10.f, 20.f);
	if (mWheel[3] == nullptr) mWheel[3] = new Wheel(*mWorld, { -15.f, 160.f }, 4.0f, 10.f, 20.f);
	if (mWheel[4] == nullptr) mWheel[4] = new Wheel(*mWorld, {  -5.f, 150.f }, 4.0f, 10.f, 20.f);
	if (mWheel[5] == nullptr) mWheel[5] = new Wheel(*mWorld, {   5.f, 150.f }, 4.0f, 10.f, 20.f);
	if (mWheel[6] == nullptr) mWheel[6] = new Wheel(*mWorld, {   15.f, 150.f }, 4.0f, 10.f, 20.f);
	if (mWheel[7] == nullptr) mWheel[7] = new Wheel(*mWorld, {   50.f, 130.f }, 3.0f, 10.f, 20.f);
	if (mWheel[8] == nullptr) mWheel[8] = new Wheel(*mWorld, {   60.f, 130.f }, 3.0f, 10.f, 20.f);
	if (mWheel[9] == nullptr) mWheel[9] = new Wheel(*mWorld, {   70.f, 130.f }, 3.0f, 10.f, 20.f);

	// Inicializacion de plataformas dinamicas
	if (mDynamicPlatform[0] == nullptr) mDynamicPlatform[0] = new DynamicPlatform(*mWorld, {   5.f, 145.f }, { 25.f,  2.5f },  0.f);
	if (mDynamicPlatform[1] == nullptr) mDynamicPlatform[1] = new DynamicPlatform(*mWorld, { -30.f, 150.f }, { 30.f,  2.5f },  0.f);
	if (mDynamicPlatform[2] == nullptr) mDynamicPlatform[2] = new DynamicPlatform(*mWorld, {  60.f, 120.f }, { 25.f,  2.5f }, 0.f);
	
	// Inicializacion de plataformas estaticas
	if (mStaticPlatform[0] == nullptr) mStaticPlatform[0] = new StaticPlatform(*mWorld, {  23.5f, 158.5f }, {  5.f,  9.5f }, b2_pi / 2);
	if (mStaticPlatform[1] == nullptr) mStaticPlatform[1] = new StaticPlatform(*mWorld, { 107.5f, 158.5f }, {  5.f,  9.5f }, b2_pi / 2);
	if (mStaticPlatform[2] == nullptr) mStaticPlatform[2] = new StaticPlatform(*mWorld, {  65.f, 153.5f }, {  70.f,  3.0f }, 0.f);

	// Inicializacion de cajas dinamicas
	if (mBox[0] == nullptr) mBox[0] = new Box(*mWorld, {  -5.f, 140.f});
	if (mBox[1] == nullptr) mBox[1] = new Box(*mWorld, {   5.f, 140.f });
	if (mBox[2] == nullptr) mBox[2] = new Box(*mWorld, {  15.f, 140.f });
	if (mBox[3] == nullptr) mBox[3] = new Box(*mWorld, {  50.f, 140.f });
	if (mBox[4] == nullptr) mBox[4] = new Box(*mWorld, {  60.f, 140.f });
	if (mBox[5] == nullptr) mBox[5] = new Box(*mWorld, {  70.f, 140.f });
	if (mBox[6] == nullptr) mBox[6] = new Box(*mWorld, {  -5.f, 130.f });
	if (mBox[7] == nullptr) mBox[7] = new Box(*mWorld, {   5.f, 130.f });
	if (mBox[8] == nullptr) mBox[8] = new Box(*mWorld, {  15.f, 130.f });
	if (mBox[9] == nullptr) mBox[9] = new Box(*mWorld, {   50.f, 120.f });
	if (mBox[10] == nullptr) mBox[10] = new Box(*mWorld, { 60.f, 120.f });
	if (mBox[11] == nullptr) mBox[11] = new Box(*mWorld, { 70.f, 120.f });

	// Inicializacion cajas estaticas
	if (mStaticBox[0] == nullptr) mStaticBox[0] = new StaticBox(*mWorld, { 120.f, 160.f});
	if (mStaticBox[1] == nullptr) mStaticBox[1] = new StaticBox(*mWorld, { 130.f, 160.f });
	if (mStaticBox[2] == nullptr) mStaticBox[2] = new StaticBox(*mWorld, { 140.f, 160.f });
	if (mStaticBox[3] == nullptr) mStaticBox[3] = new StaticBox(*mWorld, {  -5.f, 160.f });
	if (mStaticBox[4] == nullptr) mStaticBox[4] = new StaticBox(*mWorld, {   5.f, 160.f });
	if (mStaticBox[5] == nullptr) mStaticBox[5] = new StaticBox(*mWorld, {  15.f, 160.f });

	// Inicializacion pila de latas vacias
	if (mEmptyCans == nullptr) mEmptyCans = new EmptyCans(*mWorld, { 130.f, 146.f }); 
}

// Destructor
Level3::~Level3()
{

	for (int i = 0; i < 10; i++)
	{
		delete mStaticBox[i];
		delete mWheel[i];
		delete mDynamicPlatform[i];
		delete mStaticPlatform[i];
	}
	for (int i = 0; i < 20; i++)
	{
		delete mBox[i];
	}
	delete mEmptyCans;
	
}

// Método para configurar las colisiones
void Level3::CheckCollisions()
{

	mWorld->SetContactListener(mContactListener);
}

// Método para configurar las colisiones
bool Level3::UnlockedLevel() const
{
	return mUnlocked;
}

// Método para mostrar el mensaje de derrota
void Level3::ShowLoseMsg()
{

	mLevelFinish = true;
	mLevelMusic->stop();
	mStateMsg->setScale(0.25f, 0.25f);
	mStateMsg->setPosition(-40.f, 55.f);
	ShowMsg("YOU HIT THE WHELL OF DEAD");
}

// Método para manejar el daño recibido
bool Level3::GetHurt()
{

	ShowLoseMsg();
	mGetHurt = true;
	return true;
}

// Método para finalizar el nivel
bool Level3::FinishLevel()
{
	if (!mLevelFinish)
	{
		mLevelFinish = true;
		mLevelMusic->stop();
		mStateMsg->setPosition(-20.f, 55.f);
		ShowMsg("LEVEL WIN");
	}
	return true;
}

// Método para ejecutar el nivel
void Level3::RunLevel()
{
	// Limpiar
	mWindow->clear(Color(255, 218, 185)); // PeachPuff
	
	// Acercar camara
	SetCamara(0.20f);

	// visibilidad del cursor del mouse
	mWindow->setMouseCursorVisible(false);

	// Dibujar
	mFloor->Draw(*mWindow); // Piso
	mCanon->Draw(*mWindow); // Canon
	if (mRagdoll != nullptr) { mRagdoll->Draw(*mWindow); } // Ragdoll
	for (int i = 0; i < 10; i++)  { if (mWheel[i] != nullptr) mWheel[i]->Draw(*mWindow); } // Ruedas
	for (int i = 0; i < 10; i++)  { if (mStaticPlatform[i] != nullptr) mStaticPlatform[i]->Draw(*mWindow); }// Plataformas estaticas
	for (int i = 0; i < 10; i++)  { if (mDynamicPlatform[i] != nullptr) mDynamicPlatform[i]->Draw(*mWindow); }// Plataformas dinamicas
	for (int i = 0; i < 20; i++)  { if (mBox[i] != nullptr) mBox[i]->Draw(*mWindow); } // Cajas dinamicas
	for (int i = 0; i < 10; i++)  { if(mStaticBox[i] != nullptr) mStaticBox[i]->Draw(*mWindow); } // Cajas estaticas
	if (mEmptyCans != nullptr) { mEmptyCans->Draw(*mWindow); } // Pila de latas vacias
	for (int i = 0; i < 3; i++) { mWindow->draw(*mUIsp[i]); } // fondos del UI del nivel
	mWindow->draw(*mCountdownTimer); // Cronometro
	mWindow->draw(*mRagdollCounter); // Contador de ragdolls
	mWindow->draw(*mCanonPower); // Potencia de disparo
	mWindow->draw(*mCrosshairSp); // Crosshair
	
	// Mostrar
	mWindow->display();
}
