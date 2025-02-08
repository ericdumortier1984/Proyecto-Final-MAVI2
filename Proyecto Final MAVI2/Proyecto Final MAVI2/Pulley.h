#pragma once
#include "MainHeader.h"

class Pulley
{
public:

	friend class Avatar;

	Pulley(b2World& mWorld, b2Vec2 mPosition);
	~Pulley();

	void Draw(RenderWindow& mWindow);

private:

	Texture* mPulleyTx;
	Texture* mLoadTx;
	Sprite* mPulleySp;
	Sprite* mLoadSp;
	Avatar* mPulleyAvatar;
	Avatar* mLoadAvatarA;
	Avatar* mLoadAvatarB;

	b2Body* mBodyPulley = nullptr;
	b2Body* mBodyLoadA = nullptr;
	b2Body* mBodyLoadB = nullptr;
	b2BodyDef mBodyDefPulley;
	b2BodyDef mBodyDefLoadA;
	b2BodyDef mBodyDefLoadB;
	b2Fixture* mFixturePulley;
	b2Fixture* mFixtureLoadA;
	b2Fixture* mFixtureLoadB;
	b2FixtureDef mFixtureDefPulley;
	b2FixtureDef mFixtureDefLoadA;
	b2FixtureDef mFixtureDefLoadB;
	b2PulleyJoint* mPulleyJoint;

	int mID;
};
