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

	void ApplyForce(Vector2f mPositionMouse);
	void Draw(RenderWindow& mWindow);

	float Rad2Deg(float mRadians);

private:

	RectangleShape* mSfmlRagdoll[6];
	Avatar* mAvatarRagdoll[6];

	//Ragdoll
	b2Body* mBodyRagdoll[6];
	b2BodyDef mBodyDefRagdoll[6];
	b2Fixture* mFixtureRagdoll[6];
	b2FixtureDef mFixtureDefRagdoll[6];

	//Resortes
	b2DistanceJoint* mJointRagdoll[5];
	b2DistanceJointDef mJointDefRagdoll[5];
};