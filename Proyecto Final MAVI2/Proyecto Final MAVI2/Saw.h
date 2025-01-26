#pragma once
#include <iostream>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Saw
{
public:

	friend class Avatar;

	Saw(b2World& mWorld, b2Vec2 mPosition);
	~Saw();

	b2Body* GetBody() const { return mBodySaw; }
	void Draw(RenderWindow& mWindow);

private:

	Texture* mSawTx;
	Sprite* mSawSp;
	Avatar* mSawAvatar;

	b2Body* mBodySaw = nullptr;
	b2BodyDef mBodyDefSaw;
	b2Fixture* mFixtureSaw;
	b2FixtureDef mFixtureDefSaw;

	int mID;
};