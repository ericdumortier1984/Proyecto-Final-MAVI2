#include "Box.h"
#include "Avatar.h"

Box::Box(b2World& mWorld) : mID(2)
{

	mBoxTx = new Texture;
	if (!mBoxTx->loadFromFile("Assets/box.png")) { cout << "Error al cargar la textura de la caja" << endl; }
	mBoxSp = new Sprite;
	mBoxSp->setTexture(*mBoxTx);

	mBodyDefBox.type = b2_dynamicBody;
	mBodyDefBox.position = b2Vec2(50.f, 100.f);
	mBodyBox = mWorld.CreateBody(&mBodyDefBox);
	b2PolygonShape mBoxShape;
	mBoxShape.SetAsBox(4.f, 4.f);
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

	//mBoxAvatar->Draw(mWindow);
}