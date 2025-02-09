#include "StaticBox.h"
#include "Avatar.h"

// Constructor
StaticBox::StaticBox(b2World& mWorld, b2Vec2 mPosition) : mID(10)
{

	// Carga de la textura caja estatica
	mStaticBoxTx = new Texture;
	if (!mStaticBoxTx->loadFromFile("Assets/Objects/staticBox.png")) { cout << "Error al cargar la textura de la caja estatica" << endl; }
	
	// Creacion del Sprite y asignacion de su textura
	mStaticBoxSp = new Sprite;
	mStaticBoxSp->setTexture(*mStaticBoxTx);

	// Definicion del cuerpo de la caja estatica en Box2D
	mBodyDefStaticBox.type = b2_staticBody;
	mBodyDefStaticBox.position = mPosition;
	mBodyStaticBox = mWorld.CreateBody(&mBodyDefStaticBox);

	// Definicion de la forma y propiedades de la caja estatica
	b2PolygonShape mBoxShape;
	mBoxShape.SetAsBox(4.f, 4.f);
	mFixtureDefStaticBox.shape = &mBoxShape;
	mFixtureDefStaticBox.density = 0.025f;
	mFixtureDefStaticBox.restitution = 0.3f;
	mFixtureDefStaticBox.friction = 1.0f;
	mFixtureStaticBox = mBodyStaticBox->CreateFixture(&mFixtureDefStaticBox);

	// Asignacion de la identidad de el cuerpo para la caja estatica
	mBodyStaticBox->GetUserData().pointer = (uintptr_t)mID; //ID

	// Creacion del avatar de la caja estatica
	mStaticBoxAvatar = new Avatar(mBodyStaticBox, mStaticBoxSp);
}

// Destructor
StaticBox::~StaticBox()
{

	delete mStaticBoxSp;
	delete mStaticBoxTx;
	delete mStaticBoxAvatar;
}

// Metodo para dibujar la caja estatica en la ventana
void StaticBox::Draw(RenderWindow& mWindow)
{

	mStaticBoxAvatar->Draw(mWindow);
}