#include "ContactListener.h"

void ContactListener::BeginContact(b2Contact* mContact) //Se llama cuando un objeto entra en contacto
{

	//Obtiene fixture de los cuerpos
	b2Fixture* mFixtureA = mContact->GetFixtureA();
	b2Fixture* mFixtureB = mContact->GetFixtureB();

	//Obtiene body de los cuerpos
	b2Body* mBodyA = mFixtureA->GetBody();
	b2Body* mBodyB = mFixtureB->GetBody();

	//Que tipo de cuerpos son...
	// Verifica si los cuerpos tienen user data asignado 
	if (mBodyA->GetUserData().pointer && mBodyB->GetUserData().pointer)
	{ // Realiza el cast a Ragdoll 
		Ragdoll* ragdollA = reinterpret_cast<Ragdoll*>(mBodyA->GetUserData().pointer);
		Ragdoll* ragdollB = reinterpret_cast<Ragdoll*>(mBodyB->GetUserData().pointer);
		// Realiza acciones específicas cuando los Ragdolls entran en contacto 
		if (ragdollA && ragdollB)
		{ // Aquí puedes añadir el código que deseas ejecutar cuando dos Ragdolls entran en contacto 
			std::cout << "Dos Ragdolls han entrado en contacto" << endl;
		}
	}
}