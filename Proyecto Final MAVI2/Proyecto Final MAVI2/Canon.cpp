#include "Canon.h"
#include "Avatar.h"
#include "Ragdoll.h"

Canon::Canon(b2World& mWorld)
{

	mCanonTx = new Texture;
	mCanonBaseTx = new Texture;
	if (!mCanonTx->loadFromFile("Assets/Objects/canonBody.png")) { cout << "Error al cargar la textura del canion" << endl; }
	if (!mCanonBaseTx->loadFromFile("Assets/Objects/canonBase.png")) { cout << "Error al cargar la textura del pie de canion" << endl; }
	mCanonSp = new Sprite;
	mCanonBaseSp = new Sprite;
	mCanonSp->setTexture(*mCanonTx);
	mCanonBaseSp->setTexture(*mCanonBaseTx);
	mCanonBaseSp->setScale(15.f / mCanonBaseTx->getSize().x, 15.f / mCanonBaseTx->getSize().y);
	mCanonBaseSp->setPosition({ -105.5f, 152.5f });

	mBodyDefCanon.type = b2_kinematicBody;
	mBodyDefCanon.position = b2Vec2(-95.f, 154.f);
	mBodyCanon = mWorld.CreateBody(&mBodyDefCanon);
	b2PolygonShape mCanonShape;
	mCanonShape.SetAsBox(10.f, 10.f);
	mFixtureDefCanon.shape = &mCanonShape;
	mFixtureDefCanon.density = 0.3f;
	mFixtureDefCanon.restitution = 0.3f;
	mFixtureDefCanon.friction = 0.3f;
	mFixtureCanon = mBodyCanon->CreateFixture(&mFixtureDefCanon);
	mBodyCanon->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
	
	mCanonAvatar = new Avatar(mBodyCanon, mCanonSp);
}

Canon::~Canon()
{

	delete mCanonSp;
	delete mCanonBaseSp;
	delete mCanonTx; 
	delete mCanonBaseTx; 
	delete mCanonAvatar;
	delete mRagdoll;
}

void Canon::Shoot(b2World* mWorld, Vector2f mPositionMouse, RenderWindow& mWindow)
{

	Vector2f mMousePos;
	mMousePos = mWindow.mapPixelToCoords(Mouse::getPosition(mWindow));
	b2Vec2 mCanonTipPosition = mBodyCanon->GetWorldPoint(b2Vec2(11.f, -5.f)); // Ajusta según la longitud del cañón 
	mRagdoll = new Ragdoll({ mCanonTipPosition.x, mCanonTipPosition.y }, *mWorld);
	mRagdoll->ApplyForce(Vector2f(mMousePos.x - mBodyCanon->GetPosition().x, mMousePos.y - mBodyCanon->GetPosition().y));
}

void Canon::Update(Vector2f mPositionMouse)
{

	mBodyCanon->SetTransform(mBodyCanon->GetPosition(), atan2f(mPositionMouse.y - mBodyCanon->GetPosition().y, mPositionMouse.x - mBodyCanon->GetPosition().x));
}

void Canon::Draw(RenderWindow& mWindow)
{

	mCanonAvatar->Draw(mWindow);
	mWindow.draw(*mCanonBaseSp);
}

Ragdoll* Canon::GetRagdoll() 
{ 
	return mRagdoll; 
}