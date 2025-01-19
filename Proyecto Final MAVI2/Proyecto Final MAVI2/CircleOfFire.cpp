#include "CircleOfFire.h"
#include "Avatar.h"

CircleOfFire::CircleOfFire(b2World& mWorld) : mID(3)
{

	mCircleOfFireTx = new Texture;
	if (!mCircleOfFireTx->loadFromFile("Assets/circleOfFire.png")) { cout << "Error al cargar la textura del circulo de fuego" << endl; }
	mCircleOfFireSp = new Sprite;
	mCircleOfFireSp->setTexture(*mCircleOfFireTx);

	mBodyDefCircleOfFire.type = b2_staticBody;
	mBodyDefCircleOfFire.position = b2Vec2(10.f, 140.f);
	mBodyCircleOfFire = mWorld.CreateBody(&mBodyDefCircleOfFire);
	b2PolygonShape circleOfFireShape;
	circleOfFireShape.SetAsBox(8.f, 8.f);
	mFixtureDefCircleOfFire.shape = &circleOfFireShape;
	mFixtureDefCircleOfFire.isSensor = true;
	mFixtureCircleOfFire = mBodyCircleOfFire->CreateFixture(&mFixtureDefCircleOfFire);

	mBodyCircleOfFire->GetUserData().pointer = (uintptr_t)mID; //ID
	mCircleOfFireAvatar = new Avatar(mBodyCircleOfFire, mCircleOfFireSp);
}

CircleOfFire::~CircleOfFire()
{

	delete mCircleOfFireTx;
	delete mCircleOfFireSp;
	delete mCircleOfFireAvatar;
}

void CircleOfFire::Draw(RenderWindow& mWindow)
{

	mCircleOfFireAvatar->Draw(mWindow);
}