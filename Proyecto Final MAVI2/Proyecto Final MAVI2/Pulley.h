#pragma once
#include "MainHeader.h"

class Pulley
{
public:

	friend class Avatar;

	Pulley(b2World& mWorld, b2Vec2 mPosition);
	~Pulley();

	void Draw(RenderWindow& mWindow);
	b2Body* GetBody() const { return mBodyPulley; }

private:

	Texture* mPulleyTx;
	Texture* mCircleTx;
	Sprite* mPulleySp;
	Sprite* mCircleSp;
	Avatar* mPulleyAvatar;
	Avatar* mCircleAvatarA;
	Avatar* mCircleAvatarB;

	b2Body* mBodyPulley = nullptr;
	b2Body* mBodyCircleA = nullptr;
	b2Body* mBodyCircleB = nullptr;
	b2BodyDef mBodyDefPulley;
	b2BodyDef mBodyDefCircleA;
	b2BodyDef mBodyDefCircleB;
	b2Fixture* mFixturePulley;
	b2Fixture* mFixtureCircleA;
	b2Fixture* mFixtureCircleB;
	b2FixtureDef mFixtureDefPulley;
	b2FixtureDef mFixtureDefCircleA;
	b2FixtureDef mFixtureDefCircleB;
	b2PulleyJoint* mPulleyJoint;

	int mID;
};
