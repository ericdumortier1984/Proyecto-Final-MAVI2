#include "Box.h"
#include "Avatar.h"

// Constructor
Box::Box(b2World& mWorld, b2Vec2 mPosition) : mID(2)
{

	// Carga de la textura de la caja dinamica
	mBoxTx = new Texture;
	if (!mBoxTx->loadFromFile("Assets/Objects/box.png")) { cout << "Error al cargar la textura de la caja" << endl; }
	
	// Creacion de el Sprite y asignacion de la textura a la caja dinamica
	mBoxSp = new Sprite;
	mBoxSp->setTexture(*mBoxTx);

	// Definicion del cuerpo de la caja dinamica en Box2D
	mBodyDefBox.type = b2_dynamicBody;
	mBodyDefBox.position = mPosition;
	mBodyBox = mWorld.CreateBody(&mBodyDefBox);

	// Definicion de la forma de la caja dinamica como un rectangulo
	b2PolygonShape mBoxShape;
	mBoxShape.SetAsBox(3.5f, 3.5f);

	// Definicion de las propiedades del ficture de la caja dinamica
	mFixtureDefBox.shape = &mBoxShape;
	mFixtureDefBox.density = 0.025f; // 0.275
	mFixtureDefBox.restitution = 0.3f;
	mFixtureDefBox.friction = 1.0f;
	mFixtureBox = mBodyBox->CreateFixture(&mFixtureDefBox);

	// Asignacion de una identidad al cuerpo de la caja dinamica
	mBodyBox->GetUserData().pointer = (uintptr_t)mID; //ID

	// Creacion del avatar de la caja dinamica
	mBoxAvatar = new Avatar(mBodyBox, mBoxSp);
}

// Destructor
Box::~Box()
{

	delete mBoxSp;
	delete mBoxTx;
	delete mBoxAvatar;
}

// Metodo para dibujar la caja dianmica en la ventana
void Box::Draw(RenderWindow& mWindow)
{

	mBoxAvatar->Draw(mWindow);
}