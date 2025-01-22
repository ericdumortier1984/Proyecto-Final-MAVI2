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

	CircleOfFire(b2World& mWorld, b2Vec2 mPosition);
	~CircleOfFire();

	void Draw(RenderWindow& mWindow);

private:

	//Circulos
	Texture* mCircleOfFireTx;
	Sprite* mCircleOfFireSp;
	Avatar* mCircleOfFireAvatar;

	b2Body* mBodyCircleOfFire;
	b2BodyDef mBodyDefCircleOfFire;
	b2Fixture* mFixtureCircleOfFire;
	b2FixtureDef mFixtureDefCircleOfFire;

	//bases
	Texture* mBaseTx;
	Sprite* mBaseSp;
	Avatar* mBaseAvatar;

	b2Body* mBodyBase;
	b2BodyDef mBodyDefBase;
	b2Fixture* mFixtureBase;
	b2FixtureDef mFixtureDefBase;

	int mID;
};
