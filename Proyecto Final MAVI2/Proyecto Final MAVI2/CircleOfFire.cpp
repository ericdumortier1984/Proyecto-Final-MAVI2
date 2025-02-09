#include "CircleOfFire.h"
#include "Avatar.h"

// Constructor
CircleOfFire::CircleOfFire(b2World& mWorld, b2Vec2 mPosition) : mID(3)
{

	// Carga la textura del aro de fuego
	mCircleOfFireTx = new Texture;
	if (!mCircleOfFireTx->loadFromFile("Assets/Objects/fire.png")) { cout << "Error al cargar la textura del circulo de fuego" << endl; }
	
	// Creacion del Sprite y asignacion de su textura 
	mCircleOfFireSp = new Sprite;
	mCircleOfFireSp->setTexture(*mCircleOfFireTx);

	// Definicion del cuerpo del aro de fuego en Box2D
	mBodyDefCircleOfFire.type = b2_staticBody;
	mBodyDefCircleOfFire.position = mPosition;
	mBodyCircleOfFire = mWorld.CreateBody(&mBodyDefCircleOfFire);

	// Definicion de la forma y propiedades del aro de fuego
	b2PolygonShape mCircleOfFireShape;
	mCircleOfFireShape.SetAsBox(8.f, 8.f);
	mFixtureDefCircleOfFire.shape = &mCircleOfFireShape;
	mFixtureDefCircleOfFire.isSensor = true;
	mFixtureCircleOfFire = mBodyCircleOfFire->CreateFixture(&mFixtureDefCircleOfFire);

	// Asigna una identidad al cuerpo del aro de fuego
	mBodyCircleOfFire->GetUserData().pointer = (uintptr_t)mID; //ID

	// Creacion del avatar del aro de fuego
	mCircleOfFireAvatar = new Avatar(mBodyCircleOfFire, mCircleOfFireSp);

	// Carga de la textura de la base
	mBaseTx = new Texture;
	if (!mBaseTx->loadFromFile("Assets/Objects/idle2.png")) { cout << "Error al cargar la textura de las bases" << endl; }
	
	// Creacion del Sprite y asignacion de textura para la base
	mBaseSp = new Sprite;
	mBaseSp->setTexture(*mBaseTx);

	// Definicion del cuerpo de la base en Box2D
	mBodyDefBase.type = b2_staticBody;
	mBodyDefBase.position = mPosition - b2Vec2(0.f, -17.f);
	mBodyBase = mWorld.CreateBody(&mBodyDefBase);

	// Definicion de la forma y sus propiedades para la base
	b2PolygonShape mBaseShape;
	mBaseShape.SetAsBox(6.f, 6.f);
	mFixtureDefBase.shape = &mBaseShape;
	mFixtureBase = mBodyBase->CreateFixture(&mFixtureDefBase);

	// Creacion del avatar de la base
	mBaseAvatar = new Avatar(mBodyBase, mBaseSp);
	
}

// Destructor
CircleOfFire::~CircleOfFire()
{
	
	delete mCircleOfFireTx;
	delete mCircleOfFireSp;
	delete mCircleOfFireAvatar;
	delete mBaseTx;
	delete mBaseSp;
	delete mBaseAvatar;
}

// Metodo para dibujar el aro de fuego en la ventana
void CircleOfFire::Draw(RenderWindow& mWindow)
{

	mCircleOfFireAvatar->Draw(mWindow);
	mBaseAvatar->Draw(mWindow);
}