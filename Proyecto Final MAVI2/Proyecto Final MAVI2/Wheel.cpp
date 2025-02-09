#include "Wheel.h"
#include "Avatar.h"

Wheel::Wheel(b2World& mWorld, b2Vec2 mPosition, float mRadius, float mMotorSpeed, float mMaxTorque) : mID(1)
{

	mWheelTx = new Texture;
	if (!mWheelTx->loadFromFile("Assets/Objects/spikedBall.png")) { cout << "Error al cargar la textura de la rueda" << endl; }
	mWheelSp = new Sprite;
	mWheelSp->setTexture(*mWheelTx);

	mBodyDefWheel.type = b2_dynamicBody;
	mBodyDefWheel.position = mPosition;
	mBodyWheel = mWorld.CreateBody(&mBodyDefWheel);
	b2CircleShape mWheelShape;
	mWheelShape.m_radius = mRadius;
	mFixtureDefWheel.shape = &mWheelShape;
	mFixtureDefWheel.density = 0.01f;
	mFixtureWheel = mBodyWheel->CreateFixture(&mFixtureDefWheel);

	//Wheel Joint
	b2BodyDef mGroundBodydef;
	mGroundBodydef.position.Set(0.0f, 0.0f);
	b2Body* mGroundBody = mWorld.CreateBody(&mGroundBodydef);

	b2WheelJointDef mWheelJointDef;
	mWheelJointDef.Initialize(mGroundBody, mBodyWheel, mBodyWheel->GetWorldCenter(), b2Vec2(0.0f, 1.0f));
	mWheelJointDef.motorSpeed = mMotorSpeed;
	mWheelJointDef.maxMotorTorque = mMaxTorque;
	mWheelJointDef.enableMotor = true;

	mWheelJoint = (b2WheelJoint*)mWorld.CreateJoint(&mWheelJointDef);

	mBodyWheel->GetUserData().pointer = (uintptr_t)mID; //ID
	mWheelAvatar = new Avatar(mBodyWheel, mWheelSp);
}

Wheel::~Wheel()
{

	delete mWheelTx;
	delete mWheelSp;
	delete mWheelAvatar;
}

void Wheel::Draw(RenderWindow& mWindow)
{

	mWheelAvatar->Draw(mWindow);
}