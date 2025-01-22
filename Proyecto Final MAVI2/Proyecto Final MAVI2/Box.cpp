#include "Box.h"
#include "Avatar.h"

Box::Box(b2World& mWorld, b2Vec2 mPosition) : mID(2)
{

	mBoxTx = new Texture;
	if (!mBoxTx->loadFromFile("Assets/Objects/box.png")) { cout << "Error al cargar la textura de la caja" << endl; }
	mBoxSp = new Sprite;
	mBoxSp->setTexture(*mBoxTx);

	mBodyDefBox.type = b2_dynamicBody;
	mBodyDefBox.position = mPosition;
	mBodyBox = mWorld.CreateBody(&mBodyDefBox);
	b2PolygonShape mBoxShape;
	mBoxShape.SetAsBox(6.f, 6.f);
	mFixtureDefBox.shape = &mBoxShape;
	mFixtureDefBox.density = 0.1f;
	mFixtureDefBox.restitution = 0.3f;
	mFixtureDefBox.friction = 0.3f;
	mFixtureBox = mBodyBox->CreateFixture(&mFixtureDefBox);

	mBodyBox->GetUserData().pointer = (uintptr_t)mID; //ID
	mBoxAvatar = new Avatar(mBodyBox, mBoxSp);
}

Box::~Box()
{

	delete mBoxSp;
	delete mBoxTx;
	delete mBoxAvatar;
}

void Box::Draw(RenderWindow& mWindow)
{

	mBoxAvatar->Draw(mWindow);
}