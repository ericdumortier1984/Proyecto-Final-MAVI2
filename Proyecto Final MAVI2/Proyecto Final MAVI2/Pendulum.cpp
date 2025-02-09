#include "Pendulum.h"
#include "Avatar.h"

// Constructor
Pendulum::Pendulum(b2World& mWorld, b2Vec2 mPosition) : mID(5)
{

	// Carga de las texturas
	mPendulumTx = new Texture;
	mCircleTx = new Texture;
	if (!mPendulumTx->loadFromFile("Assets/Objects/pendulum.png")) {cout << "Error al cargar la textura del pendulo" << endl; }
	if (!mCircleTx->loadFromFile("Assets/Objects/wheel.png")) { cout << "Error al cargar la textura del circulo" << endl; }

	// Creacion de Sprites y asigancion de texturas
	mPendulumSp = new Sprite;
	mCircleSp = new Sprite;
	mPendulumSp->setTexture(*mPendulumTx);
	mCircleSp->setTexture(*mCircleTx);

	// Definicion de cuerpos en Box2D
	mBodyDefPendulum.type = b2_dynamicBody;
	mBodyDefPendulum.position = mPosition;
	mBodyPendulum = mWorld.CreateBody(&mBodyDefPendulum);

	mBodyDefCircle.type = b2_staticBody;
	mBodyDefCircle.position = b2Vec2(mPosition.x, mPosition.y - 5);
	mBodyCircle = mWorld.CreateBody(&mBodyDefCircle);

	// Definicion de formas y fixtures
	b2PolygonShape mPendulumShape;
	mPendulumShape.SetAsBox(3.f, 10.f);
	mFixtureDefPendulum.shape = &mPendulumShape;
	mFixtureDefPendulum.density = 0.005f;
	mFixtureDefPendulum.restitution = 0.5f;
	mFixtureDefPendulum.friction = 0.3f;
	mFixturePendulum = mBodyPendulum->CreateFixture(&mFixtureDefPendulum);

	b2CircleShape mCircleShape;
	mCircleShape.m_radius = 2.5f;
	mFixtureDefCircle.shape = &mCircleShape;
	mFixtureDefCircle.density = 0.1f;
	mFixtureDefCircle.restitution = 0.3f;
	mFixtureCircle = mBodyCircle->CreateFixture(&mFixtureDefCircle);

	// Definicion del joint
	b2RevoluteJointDef mRevoluteJointDef;
	mRevoluteJointDef.bodyA = mBodyPendulum;
	mRevoluteJointDef.bodyB = mBodyCircle;
	mRevoluteJointDef.localAnchorA.Set(0.f, -15.f); // Anclas
	mRevoluteJointDef.localAnchorB.Set(0.f, 0.f); // Anclas
	mRevoluteJoint = (b2RevoluteJoint*)mWorld.CreateJoint(&mRevoluteJointDef);

	// Asignacion de identidad al cuerpo de el pendulo
	mBodyPendulum->GetUserData().pointer = (uintptr_t)mID; //ID

	// Creacion de avatares
	mPendulumAvatar = new Avatar(mBodyPendulum, mPendulumSp);
	mCircleAvatar = new Avatar(mBodyCircle, mCircleSp);
}

// Destructor
Pendulum::~Pendulum()
{

	delete mPendulumTx;
	delete mCircleTx;
	delete mPendulumSp;
	delete mCircleSp;
	delete mPendulumAvatar;
	delete mCircleAvatar;
}

// Metodo para dibujar el pendulo en la ventana
void Pendulum::Draw(RenderWindow& mWindow)
{

	mPendulumAvatar->Draw(mWindow);
	mCircleAvatar->Draw(mWindow);
}