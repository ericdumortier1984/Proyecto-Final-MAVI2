#pragma once
#include "MainHeader.h"

class CircleOfFire
{
public:

	friend class Avatar;

	CircleOfFire(b2World& mWorld, b2Vec2 mPosition);
	~CircleOfFire();

	void Draw(RenderWindow& mWindow);

private:

	//Circulo
	Texture* mCircleOfFireTx;
	Sprite* mCircleOfFireSp;
	Avatar* mCircleOfFireAvatar;

	b2Body* mBodyCircleOfFire;
	b2BodyDef mBodyDefCircleOfFire;
	b2Fixture* mFixtureCircleOfFire;
	b2FixtureDef mFixtureDefCircleOfFire;

	//base
	Texture* mBaseTx;
	Sprite* mBaseSp;
	Avatar* mBaseAvatar;

	b2Body* mBodyBase;
	b2BodyDef mBodyDefBase;
	b2Fixture* mFixtureBase;
	b2FixtureDef mFixtureDefBase;

	int mID;
};
