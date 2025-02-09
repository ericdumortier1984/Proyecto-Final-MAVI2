#include "EmptyCans.h"
#include "Avatar.h"

// Constructor
EmptyCans::EmptyCans(b2World& mWorld, b2Vec2 mPosition) : mID(7)
{

	// Carga de la textura para las latas
	mEmptyCansTx = new Texture;
	if (!mEmptyCansTx->loadFromFile("Assets/Objects/emptyCans.png")) { cout << "Error al cargar textura de Empty Cans" << endl; }
	
	// creacion del Sprite y asignacion de su textura
	mEmptyCansSp = new Sprite;
	mEmptyCansSp->setTexture(*mEmptyCansTx);

	// Definicion del cuerpo de las latas en Box2D
	mBodyDefEmptyCans.type = b2_staticBody;
	mBodyDefEmptyCans.position = mPosition;
	mBodyEmptyCans = mWorld.CreateBody(&mBodyDefEmptyCans);

	// definicion de la forma y propiedades de las latas
	b2PolygonShape mEmptyCansShape;
	mEmptyCansShape.SetAsBox(8.0f, 8.0f);
	mFixtureDefEmptyCans.shape = &mEmptyCansShape;
	mFixtureDefEmptyCans.isSensor = true;
	mFixtureEmptyCans = mBodyEmptyCans->CreateFixture(&mFixtureDefEmptyCans);

	// Asigna una identidad al cuerpo de la latas
	mBodyEmptyCans->GetUserData().pointer = (uintptr_t)mID; //ID

	// Creacion del avatar de las latas
	mEmptyCansAvatar = new Avatar(mBodyEmptyCans, mEmptyCansSp);
}

// Destructor
EmptyCans::~EmptyCans()
{

	delete mEmptyCansTx;
	delete mEmptyCansSp;
	delete mEmptyCansAvatar;
}

// Metodo para dibujar las latas en la ventana
void EmptyCans::Draw(RenderWindow& mWindow)
{

	mEmptyCansAvatar->Draw(mWindow);
}