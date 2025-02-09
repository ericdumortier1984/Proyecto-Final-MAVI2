#include "DynamicPlatform.h"
#include "Avatar.h"

// Constructor
DynamicPlatform::DynamicPlatform(b2World& mWorld, b2Vec2 mPosition, b2Vec2 mSize, float mRotation) : mID(9)
{

	// Carga de la textura para la plataforma dinamica
	mDynamicPlatformTx = new Texture;
	if (!mDynamicPlatformTx->loadFromFile("Assets/Objects/dynamicPlatform.png")) { cout << "Error al cargar la textura de la plataforma dinamica" << endl; }
	
	// Creacion del Sprite y asignacion de su textura
	mDynamicPlatformSp = new Sprite;
	mDynamicPlatformSp->setTexture(*mDynamicPlatformTx);

	// definicion del cuerpo de la plataforma dinamica en Box2D
	mBodyDefDynamicPlatform.type = b2_dynamicBody;
	mBodyDefDynamicPlatform.position = mPosition;
	mBodyDefDynamicPlatform.angle = mRotation;
	mBodyDynamicPlatform = mWorld.CreateBody(&mBodyDefDynamicPlatform);

	// Definicion de la forma y propiedades fisicas de la plataforma dinamica
	b2PolygonShape mDynamicPlatformShape;
	mDynamicPlatformShape.SetAsBox(mSize.x / 2, mSize.y / 2);
	mFixtureDefDynamicPlatform.shape = &mDynamicPlatformShape;
	mFixtureDefDynamicPlatform.density = 0.01f;
	mFixtureDefDynamicPlatform.restitution = 0.3f;
	mFixtureDefDynamicPlatform.friction = 0.3f;
	mFixtureDynamicPlatform = mBodyDynamicPlatform->CreateFixture(&mFixtureDefDynamicPlatform);

	// Asigna una identidad al cuerpo de la plataforma dinamica
	mBodyDynamicPlatform->GetUserData().pointer = (uintptr_t)mID; // ID
	
	// Creacion del avatar de la plataforma dinamica
	mDynamicPlatformAvatar = new Avatar(mBodyDynamicPlatform, mDynamicPlatformSp);
}

// Destructor
DynamicPlatform::~DynamicPlatform()
{

	delete mDynamicPlatformTx;
	delete mDynamicPlatformSp;
	delete mDynamicPlatformAvatar;
}

// Metodo para dibujar la plataforma dinamica en la ventana
void DynamicPlatform::Draw(RenderWindow& mWindow)
{

	mDynamicPlatformAvatar->Draw(mWindow);
}