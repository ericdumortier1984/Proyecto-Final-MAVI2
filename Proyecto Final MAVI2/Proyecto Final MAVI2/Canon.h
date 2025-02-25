#pragma once
#include "MainHeader.h"

class Canon
{
public:

	friend class Avatar;
	friend class Ragdoll;

	Canon(b2World& mWorld);
	~Canon();

	Ragdoll* GetRagdoll();
	Vector2f GetPosition() const; // M�todo para obtener la posici�n del ca��n
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