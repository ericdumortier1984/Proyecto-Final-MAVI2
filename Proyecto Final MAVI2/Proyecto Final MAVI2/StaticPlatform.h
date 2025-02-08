#pragma once
#include "MainHeader.h"

class StaticPlatform
{
public:

	friend class Avatar;

	StaticPlatform(b2World& mWorld, b2Vec2 mPosition, b2Vec2 mSize, float mRotation);
	~StaticPlatform();

	void Draw(RenderWindow& mWindow);

private:

	Texture* mStaticPlatformTx;
	Sprite* mStaticPlatformSp;
	Avatar* mStaticPlatformAvatar;

	b2Body* mBodyStaticPlatform = nullptr;
	b2BodyDef mBodyDefStaticPlatform;
	b2Fixture* mFixtureStaticPlatform;
	b2FixtureDef mFixtureDefStaticPlatform;

	int mID;
};