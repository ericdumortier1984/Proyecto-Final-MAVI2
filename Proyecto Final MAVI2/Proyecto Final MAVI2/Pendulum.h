#pragma once
#include <iostream>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Pendulum
{
public:

	friend class Avatar;

	Pendulum(b2World& mWorld, b2Vec2 mPosition);
	~Pendulum();

	void Draw(RenderWindow& mWindow);
	b2Body* GetBody() const { return mBodyPendulum; }

private:

	Texture* mPendulumTx;
	Texture* mCircleTx;
	Sprite* mPendulumSp;
	Sprite* mCircleSp;
	Avatar* mPendulumAvatar;
	Avatar* mCircleAvatar;

	b2Body* mBodyPendulum = nullptr;
	b2Body* mBodyCircle = nullptr;
	b2BodyDef mBodyDefPendulum;
	b2BodyDef mBodyDefCircle;
	b2Fixture* mFixturePendulum;
	b2Fixture* mFixtureCircle;
	b2FixtureDef mFixtureDefPendulum;
	b2FixtureDef mFixtureDefCircle;
	b2RevoluteJoint* mRevoluteJoint;

	int mID;
};