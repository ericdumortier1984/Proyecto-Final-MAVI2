#include "StaticBox.h"
#include "Avatar.h"

StaticBox::StaticBox(b2World& mWorld, b2Vec2 mPosition) : mID(10)
{

	mStaticBoxTx = new Texture;
	if (!mStaticBoxTx->loadFromFile("Assets/Objects/staticBox.png")) { cout << "Error al cargar la textura de la caja estatica" << endl; }
	mStaticBoxSp = new Sprite;
	mStaticBoxSp->setTexture(*mStaticBoxTx);

	mBodyDefStaticBox.type = b2_staticBody;
	mBodyDefStaticBox.position = mPosition;
	mBodyStaticBox = mWorld.CreateBody(&mBodyDefStaticBox);
	b2PolygonShape mBoxShape;
	mBoxShape.SetAsBox(4.f, 4.f);
	mFixtureDefStaticBox.shape = &mBoxShape;
	mFixtureDefStaticBox.density = 0.025f; // 0.275
	mFixtureDefStaticBox.restitution = 0.3f;
	mFixtureDefStaticBox.friction = 1.0f;
	mFixtureStaticBox = mBodyStaticBox->CreateFixture(&mFixtureDefStaticBox);

	mBodyStaticBox->GetUserData().pointer = (uintptr_t)mID; //ID
	mStaticBoxAvatar = new Avatar(mBodyStaticBox, mStaticBoxSp);
}

StaticBox::~StaticBox()
{

	delete mStaticBoxSp;
	delete mStaticBoxTx;
	delete mStaticBoxAvatar;
}

void StaticBox::Draw(RenderWindow& mWindow)
{

	mStaticBoxAvatar->Draw(mWindow);
}