#include "Balloons.h"
#include "Avatar.h"

// Constructor
Balloons::Balloons(b2World& mWorld, b2Vec2 mPosition) : mID(4), mSpeed(0.001f)
{

	// Carga de textura del globo
	mBalloonTx = new Texture;
	if (!mBalloonTx->loadFromFile("Assets/Objects/Balloons.png")) { cout << "Error al cargar la textura de balloons" << endl; }
	
	// Creacion del Sprite del grlobo y asignacion de textura
	mBalloonSp = new Sprite;
	mBalloonSp->setTexture(*mBalloonTx);

	// Definicion del cuerpo del globo en Box2D
	mBodyDefBalloon.type = b2_staticBody;
	mBodyDefBalloon.position = mPosition;
	mBodyBalloon = mWorld.CreateBody(&mBodyDefBalloon);

	// Definicion de la forma del globo como rectangulo
	b2PolygonShape mBalloonShape;
	mBalloonShape.SetAsBox(8.0f, 8.0f);

	// definicion de las propiedades del fixture del globo
	mFixtureDefBalloon.shape = &mBalloonShape;
	mFixtureDefBalloon.isSensor = true;
	mFixtureBalloon = mBodyBalloon->CreateFixture(&mFixtureDefBalloon);

	// Asignacion de identidad al cuerpo del globo
	mBodyBalloon->GetUserData().pointer = (uintptr_t)mID; //ID

	// creacion del avatar para el globo
	mBalloonAvatar = new Avatar(mBodyBalloon, mBalloonSp);
}

// Destructor
Balloons::~Balloons()
{

	delete mBalloonTx;
	delete mBalloonSp;
	delete mBalloonAvatar;
}

// Metodo para actualizar la posicion del globo
void Balloons::Update(float mDeltaTime)
{

	// Incrementa la posición y del globo en función de la velocidad y el tiempo transcurrido
	b2Vec2 mBalloonPosition = mBodyBalloon->GetPosition();
	mBalloonPosition.y -= mSpeed * mDeltaTime;
	mBodyBalloon->SetTransform(mBalloonPosition, mBodyBalloon->GetAngle());
}

// metodo para dibujar el globo en la ventana
void Balloons::Draw(RenderWindow& mWindow)
{

	mBalloonAvatar->Draw(mWindow);
}