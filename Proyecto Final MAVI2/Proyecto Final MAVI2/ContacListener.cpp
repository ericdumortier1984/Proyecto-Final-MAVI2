#include "ContactListener.h"
#include "Game.h"

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
			//cout << "Colision:  WIN OBJECT -> OTRA COLISION << endl;"
			break;

		case 1:
			//cout << "Colision:  RAGDOLL -> WIN OBJECT << endl;";
			mBodyB->GetUserData().pointer = (uintptr_t)0;
			break;
		case 2:
			//cout << "Colision:  OTRA COLISION -> WIN OBJECT << endl;"
			break;
		case 3:
			//cout << "Colision: CIRCLE OF FIRE -> WIN OBJECT << endl;"
		default:
			break;
		}
	}

	// Logica para colisiones entre Box y Ragdoll
	if ((mID1 == 2 && mID2 == 0) || (mID1 == 0 && mID2 == 2)) 
	{ 
		cout << "[Colision: BOX -> RAGDOLL]" << endl; 
		// Logica adicional para la colision Box -> Ragdoll 
	}
	// logica para colisiones entre Circle of Fire y Ragdoll
	else if ((mID1 == 3 && mID2 == 0) || (mID1 == 0 && mID2 == 3))
	{
		cout << "[Colision: CIRCULO DE FUEGO -> RAGDOLL]" << endl; 
		// logica adicional para la colision CircleOfFire -> Ragdoll
		mGame->NextLevel();
	}
}