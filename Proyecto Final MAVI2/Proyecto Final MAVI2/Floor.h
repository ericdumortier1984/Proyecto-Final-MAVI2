#pragma once
#include "MainHeader.h"

class Floor
{
public:

	friend class Avatar;

	Floor(b2World& mWorld);
	~Floor();

	void Draw(RenderWindow& mWindow);

private:

	Texture* mFloorTx;
	Sprite* mFloorSp;
	Avatar* mFloorAvatar;

	b2Body* mBodyFloor;
	b2BodyDef mBodyDefFloor;
	b2Fixture* mFixtureFloor;
	b2FixtureDef mFixtureDefFloor;
};