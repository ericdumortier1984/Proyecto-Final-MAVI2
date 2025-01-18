#pragma once
#include <iostream>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Box
{
public:

	friend class Avatar;

	Box(b2World& mWorld);
	~Box();

	bool CheckCollision();
	void Draw(RenderWindow& mWindow);

private:

	Texture* mBoxTx;
	Sprite* mBoxSp;
	Avatar* mBoxAvatar;

	b2Body* mBodyBox;
	b2BodyDef mBodyDefBox;
	b2Fixture* mFixtureBox;
	b2FixtureDef mFixtureDefBox;

	int mID;
};