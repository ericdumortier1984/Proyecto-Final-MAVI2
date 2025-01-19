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

	//Circulos
	Texture* mCircleOfFireTx[3];
	Sprite* mCircleOfFireSp[3];
	Avatar* mCircleOfFireAvatar[3];

	b2Body* mBodyCircleOfFire[3];
	b2BodyDef mBodyDefCircleOfFire[3];
	b2Fixture* mFixtureCircleOfFire[3];
	b2FixtureDef mFixtureDefCircleOfFire[3];

	//bases
	Texture* mBaseTx[3];
	Sprite* mBaseSp[3];
	Avatar* mBaseAvatar[3];

	b2Body* mBodyBase[3];
	b2BodyDef mBodyDefBase[3];
	b2Fixture* mFixtureBase[3];
	b2FixtureDef mFixtureDefBase[3];

	int mID;
};
