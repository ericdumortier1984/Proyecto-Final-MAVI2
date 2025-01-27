#include "NewBox.h"
#include "Avatar.h"

NewBox::NewBox(b2World& mWorld, b2Vec2 mPosition) : mID(1)
{

	mNewBoxTx = new Texture;
	if (!mNewBoxTx->loadFromFile("Assets/Objects/baloons.png")) { cout << "Error al cargar la textura de la caja" << endl; }
	mNewBoxSp = new Sprite;
	mNewBoxSp->setTexture(*mNewBoxTx);

	mBodyDefNewBox.type = b2_staticBody;
	mBodyDefNewBox.position = mPosition;
	mBodyNewBox = mWorld.CreateBody(&mBodyDefNewBox);
	b2PolygonShape mNewBoxShape;
	mNewBoxShape.SetAsBox(6.f, 6.f);
	mFixtureDefNewBox.shape = &mNewBoxShape;
	mFixtureDefNewBox.density = 0.025f;
	mFixtureDefNewBox.restitution = 0.3f;
	mFixtureDefNewBox.friction = 0.3f;
	mFixtureNewBox = mBodyNewBox->CreateFixture(&mFixtureDefNewBox);

	mBodyNewBox->GetUserData().pointer = (uintptr_t)mID; //ID
	mNewBoxAvatar = new Avatar(mBodyNewBox, mNewBoxSp);
}

NewBox::~NewBox()
{

	delete mNewBoxSp;
	delete mNewBoxTx;
	delete mNewBoxAvatar;

}

void NewBox::Draw(RenderWindow& mWindow)
{

	mNewBoxAvatar->Draw(mWindow);
}