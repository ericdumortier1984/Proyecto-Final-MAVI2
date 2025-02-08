#include "StaticPlatform.h"
#include "Avatar.h"

StaticPlatform::StaticPlatform(b2World& mWorld, b2Vec2 mPosition, b2Vec2 mSize, float mRotation) : mID(8)
{

	mStaticPlatformTx = new Texture;
	if (!mStaticPlatformTx->loadFromFile("Assets/Objects/staticPlatform.png")) { cout << "Error al cargar la textura de la plataforma estatica" << endl; }
	mStaticPlatformSp = new Sprite;
	mStaticPlatformSp->setTexture(*mStaticPlatformTx);
	
	mBodyDefStaticPlatform.type = b2_staticBody;
	mBodyDefStaticPlatform.position = mPosition;
	mBodyDefStaticPlatform.angle = mRotation;
	mBodyStaticPlatform = mWorld.CreateBody(&mBodyDefStaticPlatform);
	b2PolygonShape mStaticPlatformShape;
	mStaticPlatformShape.SetAsBox(mSize.x / 2, mSize.y / 2);
	mFixtureDefStaticPlatform.shape = &mStaticPlatformShape;
	mFixtureDefStaticPlatform.density = 0.3f;
	mFixtureDefStaticPlatform.restitution = 0.3f;
	mFixtureDefStaticPlatform.friction = 0.3f;
	mFixtureStaticPlatform = mBodyStaticPlatform->CreateFixture(&mFixtureDefStaticPlatform);
	
	mBodyStaticPlatform->GetUserData().pointer = (uintptr_t)mID; // ID
	mStaticPlatformAvatar = new Avatar(mBodyStaticPlatform, mStaticPlatformSp);
}

StaticPlatform::~StaticPlatform()
{

	delete mStaticPlatformTx;
	delete mStaticPlatformSp;
	delete mStaticPlatformAvatar;
}

void StaticPlatform::Draw(RenderWindow& mWindow)
{

	mStaticPlatformAvatar->Draw(mWindow);

}