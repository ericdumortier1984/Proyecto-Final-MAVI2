#include "Saw.h"
#include "Avatar.h"

Saw::Saw(b2World& mWorld, b2Vec2 mPosition) : mID(4)
{

	mSawTx = new Texture;
	if (!mSawTx->loadFromFile("Assets/Objects/Off.png")) { cout << "Error al cargar la textura de la sierra" << endl; }
	mSawSp = new Sprite;
	mSawSp->setTexture(*mSawTx);

	mBodyDefSaw.type = b2_staticBody;
	mBodyDefSaw.position = mPosition;
	mBodySaw = mWorld.CreateBody(&mBodyDefSaw);
	b2PolygonShape mSawShape;
	mSawShape.SetAsBox(6.f, 6.f);
	mFixtureDefSaw.shape = &mSawShape;
	mFixtureDefSaw.density = 0.025f;
	mFixtureDefSaw.restitution = 0.3f;
	mFixtureDefSaw.friction = 0.3f;
	mFixtureSaw = mBodySaw->CreateFixture(&mFixtureDefSaw);

	mBodySaw->GetUserData().pointer = (uintptr_t)mID; //ID
	mSawAvatar = new Avatar(mBodySaw, mSawSp);
}

Saw::~Saw()
{

	delete mSawSp;
	delete mSawTx;
	delete mSawAvatar;

}

void Saw::Draw(RenderWindow& mWindow)
{

	mSawAvatar->Draw(mWindow);
}