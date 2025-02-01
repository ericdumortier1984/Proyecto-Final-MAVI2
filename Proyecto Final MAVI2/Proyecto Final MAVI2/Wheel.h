#pragma once
#include "MainHeader.h"

class Wheel
{
public:

	friend class Avatar;

	Wheel(b2World& mWorld, b2Vec2 mPosition);
	~Wheel();

	void Draw(RenderWindow& mWindow);

private:

	Texture* mWheelTx;
	Sprite* mWheelSp;
	Avatar* mWheelAvatar;

	b2Body* mBodyWheel = nullptr;
	b2BodyDef mBodyDefWheel;
	b2Fixture* mFixtureWheel;
	b2FixtureDef mFixtureDefWheel;
	b2WheelJoint* mWheelJoint;

	int mID;
};