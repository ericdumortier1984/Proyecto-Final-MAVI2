#include "Floor.h"
#include "Avatar.h"

// Constructor
Floor::Floor(b2World& mWorld)
{

	// Carga la textura para el piso
	mFloorTx = new Texture;
	if (!mFloorTx->loadFromFile("Assets/Objects/floor.png")) { cout << "Error al cargar la textura del piso" << endl; }
	
	// Creacion del Sprite y asignacion de su textura
	mFloorSp = new Sprite;
	mFloorSp->setTexture(*mFloorTx);

	// Definicion del cuerpo del piso en Box2D
	mBodyDefFloor.type = b2_staticBody;
	mBodyDefFloor.position = b2Vec2(0.f, 170.f);
	mBodyFloor = mWorld.CreateBody(&mBodyDefFloor);

	// Definicion de forma y propiedades del piso
	b2PolygonShape mFloorShape;
	mFloorShape.SetAsBox(190.f, 5.f);
	mFixtureDefFloor.shape = &mFloorShape;
	mFixtureDefFloor.density = 1.f;
	mFixtureDefFloor.restitution = 0.3f;
	mFixtureDefFloor.friction = 0.3f;
	mFixtureFloor = mBodyFloor->CreateFixture(&mFixtureDefFloor);

	// Creacion del avatar del piso
	mFloorAvatar = new Avatar(mBodyFloor, mFloorSp);
}

// Destructor
Floor::~Floor()
{

	delete mFloorSp;
	delete mFloorTx; 
	delete mFloorAvatar;
}

// Metodo para dibujar el piso en la ventana
void Floor::Draw(RenderWindow& mWindow)
{

	mFloorAvatar->Draw(mWindow);
}