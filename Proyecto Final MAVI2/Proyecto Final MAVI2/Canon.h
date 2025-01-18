#pragma once
#include <iostream>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Canon
{
public:

	friend class Avatar;
	friend class Ragdoll;

	Canon(b2World& mWorld);
	~Canon();

	Ragdoll* GetRagdoll();
	void Shoot(b2World* mWorld, Vector2f mPositionMouse, RenderWindow& mWindow);
	void Update(Vector2f mPositionMouse);
	void Draw(RenderWindow& mWindow);

private:

	Texture* mCanonTx;
	Texture* mCanonBaseTx;
	Sprite* mCanonSp;
	Sprite* mCanonBaseSp;
	Avatar* mCanonAvatar;
	Ragdoll* mRagdoll;

	b2Body* mBodyCanon;
	b2BodyDef mBodyDefCanon;
	b2Fixture* mFixtureCanon;
	b2FixtureDef mFixtureDefCanon;

};