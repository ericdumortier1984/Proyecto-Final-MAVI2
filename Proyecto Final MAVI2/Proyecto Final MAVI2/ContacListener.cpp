#include "ContactListener.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

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
	// logica para colisiones entre Wheel y Ragdoll
	else if ((mID1 == 1 && mID2 == 0) || (mID1 == 0 && mID2 == 1))
	{
		cout << "[COLISION: WHEEL -> RAGDOLL]" << endl;
		// logica adicional para la colision Wheel -> Ragdoll
	}
	// Logica para colisiones entre Box y Ragdoll
	if ((mID1 == 2 && mID2 == 0) || (mID1 == 0 && mID2 == 2))
	{
		cout << "[COLISION: BOX -> RAGDOLL]" << endl;
		// Logica adicional para la colision Box -> Ragdoll 
	}
	// logica para colisiones entre Circle of Fire y Ragdoll
	else if ((mID1 == 3 && mID2 == 0) || (mID1 == 0 && mID2 == 3))
	{
		cout << "[COLISION: CIRCULO DE FUEGO -> RAGDOLL]" << endl;
		// logica adicional para la colision CircleOfFire -> Ragdoll
		mLevel1->FinishLevel();
	}
	// logica para colisiones entre Saw y Ragdoll
	else if ((mID1 == 4 && mID2 == 0) || (mID1 == 0 && mID2 == 4))
	{
		cout << "[COLISION: BALLOONS -> RAGDOLL]" << endl;
		// logica adicional para la colision Balloons -> Ragdoll
		mLevel2->FinishLevel();
	}
	// logica para colisiones entre Pendulum y Ragdoll
	else if ((mID1 == 5 && mID2 == 0) || (mID1 == 0 && mID2 == 5))
	{
		cout << "[COLISION: PENDULUM -> RAGDOLL]" << endl;
		// logica adicional para la colision pendulum -> Ragdoll
	}
	// logica para colisiones entre Pulley y Ragdoll
	else if ((mID1 == 6 && mID2 == 0) || (mID1 == 0 && mID2 == 6))
	{
		cout << "[COLISION: PULLEY -> RAGDOLL]" << endl;
		// logica adicional para la colision pulley -> Ragdoll
	}
	// logica para colisones entre Empty Cans y Ragdoll
	else if ((mID1 == 7 && mID2 == 0) || (mID1 == 0 && mID2 == 7))
	{
		cout << "[COLISION: EMPTY CANS -> RAGDOLL]" << endl;
		// logica adicional para colision Empty Cans y Ragdoll
		mLevel3->FinishLevel();
	}
	// logica para colisones entre Static Platform y Ragdoll
	else if ((mID1 == 8 && mID2 == 0) || (mID1 == 0 && mID2 == 8))
	{
		cout << "[COLISION: STATIC PLATFORM -> RAGDOLL]" << endl;
		// logica adicional para colision Static Platform y Ragdoll
	}
	// logica para colisones entre Dynamic Platform y Ragdoll
	else if ((mID1 == 9 && mID2 == 0) || (mID1 == 0 && mID2 == 9))
	{
		cout << "[COLISION: DYNAMIC PLATFORM -> RAGDOLL]" << endl;
		// logica adicional para colision Dynamic Platform y Ragdoll
	}
	// logica para colisones entre Static Box y Ragdoll
	else if ((mID1 == 10 && mID2 == 0) || (mID1 == 0 && mID2 == 10))
	{
		cout << "[COLISION: STATIC BOX -> RAGDOLL]" << endl;
		// logica adicional para colision Static Box y Ragdoll
	}
}