#include "physics/ContactListener.h"
#include "physics/RigidBody.h"

namespace bgl
{
	void ContactListener::BeginContact(b2Contact* contact)
	{
		 RigidBody* rigidBodyA = reinterpret_cast<RigidBody*>(contact->GetFixtureA()->GetUserData().pointer);
		 RigidBody* rigidBodyB = reinterpret_cast<RigidBody*>(contact->GetFixtureB()->GetUserData().pointer);

		 rigidBodyA->onContact(rigidBodyB);
		 rigidBodyB->onContact(rigidBodyA);
	}

	void ContactListener::EndContact(b2Contact* contact)
	{

	}
}