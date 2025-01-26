#pragma once
#include <iostream>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class NewBox
{
public:

	friend class Avatar;

	NewBox(b2World& mWorld, b2Vec2 mPosition);
	~NewBox();

	b2Body* GetBody() const { return mBodyNewBox; }
	void Draw(RenderWindow& mWindow);

private:

	Texture* mNewBoxTx;
	Sprite* mNewBoxSp;
	Avatar* mNewBoxAvatar;

	b2Body* mBodyNewBox = nullptr;
	b2BodyDef mBodyDefNewBox;
	b2Fixture* mFixtureNewBox;
	b2FixtureDef mFixtureDefNewBox;

	int mID;
};