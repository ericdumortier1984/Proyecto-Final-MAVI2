#include "CircleOfFire.h"
#include "Avatar.h"

const int QUANTITIES = 3;

CircleOfFire::CircleOfFire(b2World& mWorld) : mID(3)
{

	b2Vec2 mCirclePOS[QUANTITIES] = { b2Vec2(10.f, 145.f), b2Vec2(50.f, 100.f), b2Vec2(90.f, 60.f) }; 
	b2Vec2 mBasePOS[QUANTITIES] = { b2Vec2(10.f, 160.f), b2Vec2(50.f, 115.f), b2Vec2(90.f, 75.f) }; 
	float mBaseHIGHT[QUANTITIES] = { 8.f, 8.f, 8.f };

	for (int i = 0; i < 3; i++)
	{
		mCircleOfFireTx[i] = new Texture;
		if (!mCircleOfFireTx[i]->loadFromFile("Assets/circleOfFire.png")) { cout << "Error al cargar la textura del circulo de fuego" << endl; }
		mCircleOfFireSp[i] = new Sprite;
		mCircleOfFireSp[i]->setTexture(*mCircleOfFireTx[i]);

		mBodyDefCircleOfFire[i].type = b2_staticBody;
		mBodyDefCircleOfFire[i].position = mCirclePOS[i];
		mBodyCircleOfFire[i] = mWorld.CreateBody(&mBodyDefCircleOfFire[i]);
		b2PolygonShape mCircleOfFireShape;
		mCircleOfFireShape.SetAsBox(8.f, 8.f);
		mFixtureDefCircleOfFire[i].shape = &mCircleOfFireShape;
		mFixtureDefCircleOfFire[i].isSensor = true;
		mFixtureCircleOfFire[i] = mBodyCircleOfFire[i]->CreateFixture(&mFixtureDefCircleOfFire[i]);

		mBodyCircleOfFire[i]->GetUserData().pointer = (uintptr_t)mID; //ID
		mCircleOfFireAvatar[i] = new Avatar(mBodyCircleOfFire[i], mCircleOfFireSp[i]);

		mBaseTx[i] = new Texture;
		if (!mBaseTx[i]->loadFromFile("Assets/idle2.png")) { cout << "Error al cargar la textura de las bases" << endl; }
		mBaseSp[i] = new Sprite;
		mBaseSp[i]->setTexture(*mBaseTx[i]);

		mBodyDefBase[i].type = b2_staticBody;
		mBodyDefBase[i].position = mBasePOS[i];
		mBodyBase[i] = mWorld.CreateBody(&mBodyDefBase[i]);
		b2PolygonShape mBaseShape;
		mBaseShape.SetAsBox(8.f, mBaseHIGHT[i]);
		mFixtureDefBase[i].shape = &mBaseShape;
		mFixtureBase[i] = mBodyBase[i]->CreateFixture(&mFixtureDefBase[i]);

		mBaseAvatar[i] = new Avatar(mBodyBase[i], mBaseSp[i]);
	}
}

CircleOfFire::~CircleOfFire()
{

	for (int i = 0; i < 3; i++) 
	{
		delete mCircleOfFireTx[i];
		delete mCircleOfFireSp[i];
		delete mCircleOfFireAvatar[i];
		delete mBaseTx[i];
		delete mBaseSp[i];
		delete mBaseAvatar[i];
	}
}

void CircleOfFire::Draw(RenderWindow& mWindow)
{

	for (int i = 0; i < 3; i++ ) 
	{
		mCircleOfFireAvatar[i]->Draw(mWindow);
		mBaseAvatar[i]->Draw(mWindow);
	}
}