#include "CircleOfFire.h"
#include "Avatar.h"

CircleOfFire::CircleOfFire(b2World& mWorld, b2Vec2 mPosition) : mID(3)
{

	mCircleOfFireTx = new Texture;
	if (!mCircleOfFireTx->loadFromFile("Assets/Objects/fire.png")) { cout << "Error al cargar la textura del circulo de fuego" << endl; }
	mCircleOfFireSp = new Sprite;
	mCircleOfFireSp->setTexture(*mCircleOfFireTx);

	mBodyDefCircleOfFire.type = b2_staticBody;
	mBodyDefCircleOfFire.position = mPosition;
	mBodyCircleOfFire = mWorld.CreateBody(&mBodyDefCircleOfFire);
	b2PolygonShape mCircleOfFireShape;
	mCircleOfFireShape.SetAsBox(8.f, 8.f);
	mFixtureDefCircleOfFire.shape = &mCircleOfFireShape;
	mFixtureDefCircleOfFire.isSensor = true;
	mFixtureCircleOfFire = mBodyCircleOfFire->CreateFixture(&mFixtureDefCircleOfFire);

	mBodyCircleOfFire->GetUserData().pointer = (uintptr_t)mID; //ID
	mCircleOfFireAvatar = new Avatar(mBodyCircleOfFire, mCircleOfFireSp);

	mBaseTx = new Texture;
	if (!mBaseTx->loadFromFile("Assets/Objects/idle2.png")) { cout << "Error al cargar la textura de las bases" << endl; }
	mBaseSp = new Sprite;
	mBaseSp->setTexture(*mBaseTx);

	mBodyDefBase.type = b2_staticBody;
	mBodyDefBase.position = mPosition - b2Vec2(0.f, -17.f);
	mBodyBase = mWorld.CreateBody(&mBodyDefBase);
	b2PolygonShape mBaseShape;
	mBaseShape.SetAsBox(6.f, 6.f);
	mFixtureDefBase.shape = &mBaseShape;
	mFixtureBase = mBodyBase->CreateFixture(&mFixtureDefBase);

	mBaseAvatar = new Avatar(mBodyBase, mBaseSp);
	
}

CircleOfFire::~CircleOfFire()
{
	
	delete mCircleOfFireTx;
	delete mCircleOfFireSp;
	delete mCircleOfFireAvatar;
	delete mBaseTx;
	delete mBaseSp;
	delete mBaseAvatar;
}

void CircleOfFire::Draw(RenderWindow& mWindow)
{

	mCircleOfFireAvatar->Draw(mWindow);
	mBaseAvatar->Draw(mWindow);
}