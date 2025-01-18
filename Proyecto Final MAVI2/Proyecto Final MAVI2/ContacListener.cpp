#include "ContactListener.h"

//Resuelve las colisiones basadas en la identidad de cada objeto
void ContactListener::BeginContact(b2Contact* mContact) 
{

	CheckAABB(mContact->GetFixtureA(), mContact->GetFixtureB());
	CheckAABB(mContact->GetFixtureB(), mContact->GetFixtureA());
}

void ContactListener::EndContact(b2Contact* mContact) 
{

}

void ContactListener::CheckAABB(b2Fixture* mFixtureA, b2Fixture* mFixtureB) 
{
	b2Body* mBodyA = mFixtureA->GetBody();

	b2Body* mBodyB = mFixtureB->GetBody();

	int mID1 = (int)mBodyA->GetUserData().pointer;
	int mID2 = (int)mBodyB->GetUserData().pointer;

	if (mID1 == 0) 
	{
		switch (mID2)
		{
		case 0:
			cout << "---------------Colision:  WIN OBJECT -> OTRA COLISION--------------\n";
			break;

		case 1:
			cout << "---------------Colision:  RAGDOLL -> WIN OBJECT--------------\n";
			mBodyB->GetUserData().pointer = (uintptr_t)0;
			break;
		case 2:
			cout << "---------------Colision:  OTRA COLISION -> WIN OBJECT--------------\n";
			break;

		default:
			break;
		}
	}
}