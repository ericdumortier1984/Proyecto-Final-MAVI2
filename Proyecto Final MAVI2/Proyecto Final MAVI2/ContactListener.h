#pragma once
#include <box2d/box2d.h>
#include "Ragdoll.h"
#include "Box.h"
#include <iostream>

class ContactListener : public b2ContactListener
{
public:

    void BeginContact(b2Contact* mContact) override;
};