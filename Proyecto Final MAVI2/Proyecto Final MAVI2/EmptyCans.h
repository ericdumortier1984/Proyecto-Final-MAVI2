#pragma once
#include "MainHeader.h"

class EmptyCans
{
public:

	friend class Avatar;

	EmptyCans(b2World& mWorld, b2Vec2 mPosition);
	~EmptyCans();

	void Draw(RenderWindow& mWindow);

private:

	Texture* mEmptyCansTx;
	Sprite* mEmptyCansSp;
	Avatar* mEmptyCansAvatar;

	b2Body* mBodyEmptyCans = nullptr;
	b2BodyDef mBodyDefEmptyCans;
	b2Fixture* mFixtureEmptyCans;
	b2FixtureDef mFixtureDefEmptyCans;

	int mID;
};