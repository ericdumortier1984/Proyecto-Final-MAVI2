#include "Balloons.h"
#include "Avatar.h"

Balloons::Balloons(b2World& mWorld, b2Vec2 mPosition) : mID(4), mSpeed(0.001f)
{

	mBalloonTx = new Texture;
	if (!mBalloonTx->loadFromFile("Assets/Objects/Balloons.png")) { cout << "Error al cargar la textura de balloons" << endl; }
	mBalloonSp = new Sprite;
	mBalloonSp->setTexture(*mBalloonTx);

	mBodyDefBalloon.type = b2_staticBody;
	mBodyDefBalloon.position = mPosition;
	mBodyBalloon = mWorld.CreateBody(&mBodyDefBalloon);
	b2PolygonShape mBalloonShape;
	mBalloonShape.SetAsBox(8.0f, 8.0f);
	mFixtureDefBalloon.shape = &mBalloonShape;
	mFixtureDefBalloon.isSensor = true;
	mFixtureBalloon = mBodyBalloon->CreateFixture(&mFixtureDefBalloon);

	mBodyBalloon->GetUserData().pointer = (uintptr_t)mID; //ID
	mBalloonAvatar = new Avatar(mBodyBalloon, mBalloonSp);
}

Balloons::~Balloons()
{

	delete mBalloonTx;
	delete mBalloonSp;
	delete mBalloonAvatar;
}

void Balloons::Update(float mDeltaTime)
{

	// Incrementa la posición y del globo en función de la velocidad y el tiempo transcurrido
	b2Vec2 mBalloonPosition = mBodyBalloon->GetPosition();
	mBalloonPosition.y -= mSpeed * mDeltaTime;
	mBodyBalloon->SetTransform(mBalloonPosition, mBodyBalloon->GetAngle());
}

void Balloons::Draw(RenderWindow& mWindow)
{

	mBalloonAvatar->Draw(mWindow);
}