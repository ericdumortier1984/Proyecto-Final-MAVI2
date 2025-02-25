#pragma once
#include "MainHeader.h"

class Balloons
{
public:

	friend class Avatar;

	Balloons(b2World& mWorld, b2Vec2 mPosition);
	~Balloons();

	void Update(float mDeltaTime);
	void Draw(RenderWindow& mWindow);

private:

	Texture* mBalloonTx;
	Sprite* mBalloonSp;
	Avatar* mBalloonAvatar;

	b2Body* mBodyBalloon = nullptr;
	b2BodyDef mBodyDefBalloon;
	b2Fixture* mFixtureBalloon;
	b2FixtureDef mFixtureDefBalloon;

	float mSpeed; // Velocidad de ascenso
	int mID;
};