#pragma once
#include <iostream>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class CircleOfFire
{
public:

	friend class Avatar;

	CircleOfFire(b2World& mWorld);
	~CircleOfFire();

	void Draw(RenderWindow& mWindow);

private:

	Texture* mCircleOfFireTx;
	Sprite* mCircleOfFireSp;
	Avatar* mCircleOfFireAvatar;

	b2Body* mBodyCircleOfFire;
	b2BodyDef mBodyDefCircleOfFire;
	b2Fixture* mFixtureCircleOfFire;
	b2FixtureDef mFixtureDefCircleOfFire;

	int mID;
};
