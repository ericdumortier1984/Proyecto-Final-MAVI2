#include "StaticPlatform.h"
#include "Avatar.h"

StaticPlatform::StaticPlatform(b2World& mWorld, b2Vec2 mPosition, b2Vec2 mSize, float mRotation) : mID(8)
{

	// Craga la textura 
	mStaticPlatformTx = new Texture;
	if (!mStaticPlatformTx->loadFromFile("Assets/Objects/staticPlatform.png")) { cout << "Error al cargar la textura de la plataforma estatica" << endl; }
	
	// Creacion del Sprite y asignacion de su textura
	mStaticPlatformSp = new Sprite;
	mStaticPlatformSp->setTexture(*mStaticPlatformTx);
	
	// Definicion del cuerpo de la plataforma estatica en Box2D
	mBodyDefStaticPlatform.type = b2_staticBody;
	mBodyDefStaticPlatform.position = mPosition;
	mBodyDefStaticPlatform.angle = mRotation;
	mBodyStaticPlatform = mWorld.CreateBody(&mBodyDefStaticPlatform);

	// Definicion de la forma de la plataforma estatica
	b2PolygonShape mStaticPlatformShape;
	mStaticPlatformShape.SetAsBox(mSize.x / 2, mSize.y / 2);

	// Definicion de las propiedades de la plataforma estatica
	mFixtureDefStaticPlatform.shape = &mStaticPlatformShape;
	mFixtureDefStaticPlatform.density = 0.3f;
	mFixtureDefStaticPlatform.restitution = 0.3f;
	mFixtureDefStaticPlatform.friction = 0.3f;
	mFixtureStaticPlatform = mBodyStaticPlatform->CreateFixture(&mFixtureDefStaticPlatform);
	
	// Asignacion de una identidad al cuerpo de la plataforma estatica
	mBodyStaticPlatform->GetUserData().pointer = (uintptr_t)mID; // ID

	// Creacion del avatar de la plataforma estatica
	mStaticPlatformAvatar = new Avatar(mBodyStaticPlatform, mStaticPlatformSp);
}

// Destructor
StaticPlatform::~StaticPlatform()
{

	delete mStaticPlatformTx;
	delete mStaticPlatformSp;
	delete mStaticPlatformAvatar;
}

// Metodo para dibujar la plataforma estaica en la ventana
void StaticPlatform::Draw(RenderWindow& mWindow)
{

	mStaticPlatformAvatar->Draw(mWindow);
}