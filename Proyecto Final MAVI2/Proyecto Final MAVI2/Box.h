#pragma once
#include "MainHeader.h"

class Box
{
public:

	friend class Avatar;

	Box(b2World& mWorld, b2Vec2 mPosition);
	~Box();

	void Draw(RenderWindow& mWindow);

private:

	Texture* mBoxTx;
	Sprite* mBoxSp;
	Avatar* mBoxAvatar;

	b2Body* mBodyBox = nullptr;
	b2BodyDef mBodyDefBox;
	b2Fixture* mFixtureBox;
	b2FixtureDef mFixtureDefBox;

	int mID;
};