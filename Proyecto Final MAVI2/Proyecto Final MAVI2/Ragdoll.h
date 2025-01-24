#pragma once
#include<box2d/box2d.h>
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Ragdoll
{
public:

	friend class Avatar;

	Ragdoll(Vector2f mPositionRagdoll, b2World& mWorld);
	~Ragdoll();

	float Rad2Deg(float mRadians);
	int GetUserData();
	void ApplyForce(Vector2f mPositionMouse);
	void Draw(RenderWindow& mWindow);

private:

	Texture* mTextureHead;
	Texture* mTextureTorso;
	Texture* mTextureArmLeft;
	Texture* mTextureArmRight;
	Texture* mTextureLegLeft;
	Texture* mTextureLegRight;
	Sprite* mSfmlRagdoll[6];
	Avatar* mAvatarRagdoll[6];

	//Ragdoll
	b2Body* mBodyRagdoll[6];
	b2BodyDef mBodyDefRagdoll[6];
	b2Fixture* mFixtureRagdoll[6];
	b2FixtureDef mFixtureDefRagdoll[6];

	//Resortes
	b2DistanceJoint* mJointRagdoll[5];
	b2DistanceJointDef mJointDefRagdoll[5];

	int mID;
};