#include "Canon.h"
#include "Avatar.h"
#include "Ragdoll.h"

// Constructor
Canon::Canon(b2World& mWorld)
{

	// Carga de las texturas para el canon y su base
	mCanonTx = new Texture;
	mCanonBaseTx = new Texture;
	if (!mCanonTx->loadFromFile("Assets/Objects/canonBody.png")) { cout << "Error al cargar la textura del canion" << endl; }
	if (!mCanonBaseTx->loadFromFile("Assets/Objects/canonBase.png")) { cout << "Error al cargar la textura del pie de canion" << endl; }
	
	// Creacion de los Sprites y asignacion de sus texturas
	mCanonSp = new Sprite;
	mCanonBaseSp = new Sprite;
	mCanonSp->setTexture(*mCanonTx);
	mCanonBaseSp->setTexture(*mCanonBaseTx);
	mCanonBaseSp->setScale(15.f / mCanonBaseTx->getSize().x, 15.f / mCanonBaseTx->getSize().y);
	mCanonBaseSp->setPosition({ -105.5f, 152.5f });

	// Definicion del cuerpo del canon en el mundo Box2D
	mBodyDefCanon.type = b2_kinematicBody;
	mBodyDefCanon.position = b2Vec2(-95.f, 154.f);
	mBodyCanon = mWorld.CreateBody(&mBodyDefCanon);

	// Definicion de la forma en rectangulo y las propiedades fisicas del canon
	b2PolygonShape mCanonShape;
	mCanonShape.SetAsBox(10.f, 10.f);
	mFixtureDefCanon.shape = &mCanonShape;
	mFixtureDefCanon.density = 0.3f;
	mFixtureDefCanon.restitution = 0.3f;
	mFixtureDefCanon.friction = 0.3f;
	mFixtureCanon = mBodyCanon->CreateFixture(&mFixtureDefCanon);

	// Creacion del avatar del canon
	mCanonAvatar = new Avatar(mBodyCanon, mCanonSp);
}

// Destructor
Canon::~Canon()
{

	delete mCanonSp;
	delete mCanonBaseSp;
	delete mCanonTx; 
	delete mCanonBaseTx; 
	delete mCanonAvatar;
	delete mRagdoll;
}

// Metodo para disparar el canon
void Canon::Shoot(b2World* mWorld, Vector2f mPositionMouse, RenderWindow& mWindow)
{

	// Obtencion de la posicion del mouse en coordenadas del mundo
	Vector2f mMousePos;
	mMousePos = mWindow.mapPixelToCoords(Mouse::getPosition(mWindow));

	// Posicion de la punta del canon
	b2Vec2 mCanonTipPosition = mBodyCanon->GetWorldPoint(b2Vec2(11.f, -5.f)); // Ajusta según la longitud del cañón 
	
	// creacion de un nuevo ragdoll en la posicion de la punta del canon
	mRagdoll = new Ragdoll({ mCanonTipPosition.x, mCanonTipPosition.y }, *mWorld);

	// Aplicacion de fuerza al ragdoll en direccion al mouse
	mRagdoll->ApplyForce(Vector2f(mMousePos.x - mBodyCanon->GetPosition().x, mMousePos.y - mBodyCanon->GetPosition().y));
}

// Metodo para actualizar la orientacion del canon
void Canon::Update(Vector2f mPositionMouse)
{

	// Ajuste de la rotacion del canon en funcion de la posicion del mouse
	mBodyCanon->SetTransform(mBodyCanon->GetPosition(), atan2f(mPositionMouse.y - mBodyCanon->GetPosition().y, mPositionMouse.x - mBodyCanon->GetPosition().x));
}

// Metodo para dibujar el canon en la ventana
void Canon::Draw(RenderWindow& mWindow)
{

	mCanonAvatar->Draw(mWindow);
	mWindow.draw(*mCanonBaseSp);
}

// Metodo para obtener el ragdoll actual
Ragdoll* Canon::GetRagdoll() 
{ 
	return mRagdoll; 
}

// Metodo para obtener la posicion del canon
Vector2f Canon::GetPosition() const
{
	return mCanonSp->getPosition(); // Devuelve la posición del sprite del cañón
}