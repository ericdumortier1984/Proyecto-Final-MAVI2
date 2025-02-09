#pragma once
#include "mainHeader.h"
#include "Ragdoll.h"

class ContactListener : public b2ContactListener
{
public:

    friend class Level1;
    friend class Level2;
    friend class Level3;

    ContactListener(Level1* level1) : mLevel1(level1) {};
    ContactListener(Level2* level2) : mLevel2(level2) {};
    ContactListener(Level3* level3) : mLevel3(level3) {};

    void BeginContact(b2Contact* mContact);
    void EndContact(b2Contact* mContact);
    void CheckTypeOfCollision(b2Fixture* mFixtureA, b2Fixture* mFixtureB);

private:

    Level1* mLevel1 = nullptr;
    Level2* mLevel2 = nullptr;
    Level3* mLevel3 = nullptr;
};
