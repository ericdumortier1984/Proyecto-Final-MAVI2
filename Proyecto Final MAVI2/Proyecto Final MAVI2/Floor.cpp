#include "Floor.h"
#include "Avatar.h"

Floor::Floor(b2World& mWorld)
{
	mFloorTx = new Texture;
	if (!mFloorTx->loadFromFile("Assets/floor.png")) { cout << "Error al cargar la textura del piso" << endl; }
	mFloorSp = new Sprite;
	mFloorSp->setTexture(*mFloorTx);

	mBodyDefFloor.type = b2_staticBody;
	mBodyDefFloor.position = b2Vec2(0.f, 170.f);
	mBodyFloor = mWorld.CreateBody(&mBodyDefFloor);
	b2PolygonShape mFloorShape;
	mFloorShape.SetAsBox(190.f, 5.f);
	mFixtureDefFloor.shape = &mFloorShape;
	mFixtureDefFloor.density = 1.f;
	mFixtureDefFloor.restitution = 0.3f;
	mFixtureDefFloor.friction = 0.3f;
	mFixtureFloor = mBodyFloor->CreateFixture(&mFixtureDefFloor);
	mBodyFloor->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

	mFloorAvatar = new Avatar(mBodyFloor, mFloorSp);
}

Floor::~Floor()
{

	delete mFloorSp;
}

void Floor::Draw(RenderWindow& mWindow)
{

	mFloorAvatar->Draw(mWindow);
}