#pragma once
#include "MainHeader.h"

class DynamicPlatform
{
public:

	friend class Avatar;

	DynamicPlatform(b2World& mWorld, b2Vec2 mPosition, b2Vec2 mSize, float mRotation);
	~DynamicPlatform();

	void Draw(RenderWindow& mWindow);

private:

	Texture* mDynamicPlatformTx;
	Sprite* mDynamicPlatformSp;
	Avatar* mDynamicPlatformAvatar;

	b2Body* mBodyDynamicPlatform = nullptr;
	b2BodyDef mBodyDefDynamicPlatform;
	b2Fixture* mFixtureDynamicPlatform;
	b2FixtureDef mFixtureDefDynamicPlatform;

	int mID;
};