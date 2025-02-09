#include "Wheel.h"
#include "Avatar.h"

Wheel::Wheel(b2World& mWorld, b2Vec2 mPosition, float mRadius, float mMotorSpeed, float mMaxTorque) : mID(1)
{

	// Carga la textura de la rueda
	mWheelTx = new Texture;
	if (!mWheelTx->loadFromFile("Assets/Objects/spikedBall.png")) { cout << "Error al cargar la textura de la rueda" << endl; }
	
	// Creacion del Sprite de las rueda y asignacion de su textura
	mWheelSp = new Sprite;
	mWheelSp->setTexture(*mWheelTx);

	// Definicion del cuerpo de la rueda en Box2D
	mBodyDefWheel.type = b2_dynamicBody;
	mBodyDefWheel.position = mPosition;
	mBodyWheel = mWorld.CreateBody(&mBodyDefWheel);

	// Definicion de la forma de la rueda
	b2CircleShape mWheelShape;
	mWheelShape.m_radius = mRadius;

	// Definicion de las propiedades fisicas de la rueda
	mFixtureDefWheel.shape = &mWheelShape;
	mFixtureDefWheel.density = 0.01f;
	mFixtureWheel = mBodyWheel->CreateFixture(&mFixtureDefWheel);

	// Definicion de cuerpo base para la union de la rueda
	b2BodyDef mGroundBodydef;
	mGroundBodydef.position.Set(0.0f, 0.0f);
	b2Body* mGroundBody = mWorld.CreateBody(&mGroundBodydef);

	// Definicion de la union de la rueda
	b2WheelJointDef mWheelJointDef;
	mWheelJointDef.Initialize(mGroundBody, mBodyWheel, mBodyWheel->GetWorldCenter(), b2Vec2(0.0f, 1.0f));
	mWheelJointDef.motorSpeed = mMotorSpeed;
	mWheelJointDef.maxMotorTorque = mMaxTorque;
	mWheelJointDef.enableMotor = true;

	// Creacion de la union de la rueda en Box2D
	mWheelJoint = (b2WheelJoint*)mWorld.CreateJoint(&mWheelJointDef);

	// Asignacion de una identidad al cuerpo de la rueda
	mBodyWheel->GetUserData().pointer = (uintptr_t)mID; //ID

	// Creacion del avatar de la rueda
	mWheelAvatar = new Avatar(mBodyWheel, mWheelSp);
}

// Destructor
Wheel::~Wheel()
{

	delete mWheelTx;
	delete mWheelSp;
	delete mWheelAvatar;
}

// Metodo para dibujar la rueda en la ventana
void Wheel::Draw(RenderWindow& mWindow)
{

	mWheelAvatar->Draw(mWindow);
}