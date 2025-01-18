#pragma once
#include <box2d/box2d.h>
#include "Ragdoll.h"
#include "Box.h"

class ContactListener : public b2ContactListener
{
public:

    void BeginContact(b2Contact* mContact);
    void EndContact(b2Contact* mContact);
    void CheckAABB(b2Fixture* mFixtureA, b2Fixture* mFixtureB);
};