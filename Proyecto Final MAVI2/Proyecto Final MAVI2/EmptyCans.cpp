#include "EmptyCans.h"
#include "Avatar.h"

EmptyCans::EmptyCans(b2World& mWorld, b2Vec2 mPosition) : mID(7)
{

	mEmptyCansTx = new Texture;
	if (!mEmptyCansTx->loadFromFile("Assets/Objects/emptyCans.png")) { cout << "Error al cargar textura de Empty Cans" << endl; }
	mEmptyCansSp = new Sprite;
	mEmptyCansSp->setTexture(*mEmptyCansTx);

	mBodyDefEmptyCans.type = b2_staticBody;
	mBodyDefEmptyCans.position = mPosition;
	mBodyEmptyCans = mWorld.CreateBody(&mBodyDefEmptyCans);
	b2PolygonShape mEmptyCansShape;
	mEmptyCansShape.SetAsBox(8.0f, 8.0f);
	mFixtureDefEmptyCans.shape = &mEmptyCansShape;
	mFixtureDefEmptyCans.isSensor = true;
	mFixtureEmptyCans = mBodyEmptyCans->CreateFixture(&mFixtureDefEmptyCans);

	mBodyEmptyCans->GetUserData().pointer = (uintptr_t)mID; //ID
	mEmptyCansAvatar = new Avatar(mBodyEmptyCans, mEmptyCansSp);
}

EmptyCans::~EmptyCans()
{

	delete mEmptyCansTx;
	delete mEmptyCansSp;
	delete mEmptyCansAvatar;
}

void EmptyCans::Draw(RenderWindow& mWindow)
{

	mEmptyCansAvatar->Draw(mWindow);
}