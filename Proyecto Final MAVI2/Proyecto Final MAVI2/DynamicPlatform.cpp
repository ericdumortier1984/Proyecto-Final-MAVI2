#include "DynamicPlatform.h"
#include "Avatar.h"

DynamicPlatform::DynamicPlatform(b2World& mWorld, b2Vec2 mPosition, b2Vec2 mSize, float mRotation) : mID(9)
{

	mDynamicPlatformTx = new Texture;
	if (!mDynamicPlatformTx->loadFromFile("Assets/Objects/dynamicPlatform.png")) { cout << "Error al cargar la textura de la plataforma dinamica" << endl; }
	mDynamicPlatformSp = new Sprite;
	mDynamicPlatformSp->setTexture(*mDynamicPlatformTx);

	mBodyDefDynamicPlatform.type = b2_dynamicBody;
	mBodyDefDynamicPlatform.position = mPosition;
	mBodyDefDynamicPlatform.angle = mRotation;
	mBodyDynamicPlatform = mWorld.CreateBody(&mBodyDefDynamicPlatform);
	b2PolygonShape mDynamicPlatformShape;
	mDynamicPlatformShape.SetAsBox(mSize.x / 2, mSize.y / 2);
	mFixtureDefDynamicPlatform.shape = &mDynamicPlatformShape;
	mFixtureDefDynamicPlatform.density = 0.01f;
	mFixtureDefDynamicPlatform.restitution = 0.3f;
	mFixtureDefDynamicPlatform.friction = 0.3f;
	mFixtureDynamicPlatform = mBodyDynamicPlatform->CreateFixture(&mFixtureDefDynamicPlatform);

	mBodyDynamicPlatform->GetUserData().pointer = (uintptr_t)mID; // ID
	mDynamicPlatformAvatar = new Avatar(mBodyDynamicPlatform, mDynamicPlatformSp);
}

DynamicPlatform::~DynamicPlatform()
{

	delete mDynamicPlatformTx;
	delete mDynamicPlatformSp;
	delete mDynamicPlatformAvatar;
}

void DynamicPlatform::Draw(RenderWindow& mWindow)
{

	mDynamicPlatformAvatar->Draw(mWindow);

}