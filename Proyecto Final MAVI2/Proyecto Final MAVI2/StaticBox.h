#pragma once
#include "MainHeader.h"

class StaticBox
{
public:

	friend class Avatar;

	StaticBox(b2World& mWorld, b2Vec2 mPosition);
	~StaticBox();

	void Draw(RenderWindow& mWindow);

private:

	Texture* mStaticBoxTx;
	Sprite* mStaticBoxSp;
	Avatar* mStaticBoxAvatar;

	b2Body* mBodyStaticBox = nullptr;
	b2BodyDef mBodyDefStaticBox;
	b2Fixture* mFixtureStaticBox;
	b2FixtureDef mFixtureDefStaticBox;

	int mID;
};