#include "physics/ContactListener.h"
#include "physics/RigidBody.h"
#include <string>
#include <spdlog/spdlog.h>
#include <box2d/box2d.h>

namespace bgl
{
	void ContactListener::BeginContact(b2Contact* contact)
	{
		 RigidBody* rigidBodyA = reinterpret_cast<RigidBody*>(contact->GetFixtureA()->GetUserData().pointer);
		 RigidBody* rigidBodyB = reinterpret_cast<RigidBody*>(contact->GetFixtureB()->GetUserData().pointer);

		 b2Vec2 b2collisionNormal = contact->GetManifold()->localNormal;
		 sf::Vector2f collisionNormal{b2collisionNormal.x, b2collisionNormal.y};

		 rigidBodyA->beginContact(rigidBodyB, collisionNormal);
		 rigidBodyB->beginContact(rigidBodyA, collisionNormal);

		 spdlog::info("BeginContact collision normal: x: "  + std::to_string(contact->GetManifold()->localNormal.x) 
			 + " y: " + std::to_string(contact->GetManifold()->localNormal.y));
	}

	void ContactListener::EndContact(b2Contact* contact)
	{
		RigidBody* rigidBodyA = reinterpret_cast<RigidBody*>(contact->GetFixtureA()->GetUserData().pointer);
		RigidBody* rigidBodyB = reinterpret_cast<RigidBody*>(contact->GetFixtureB()->GetUserData().pointer);

		b2Vec2 b2collisionNormal = contact->GetManifold()->localNormal;
		sf::Vector2f collisionNormal{ b2collisionNormal.x, b2collisionNormal.y };

		rigidBodyA->endContact(rigidBodyB, collisionNormal);
		rigidBodyB->endContact(rigidBodyA, collisionNormal);

		spdlog::info("EndContact collision normal: x: " + std::to_string(contact->GetManifold()->localNormal.x)
			+ " y: " + std::to_string(contact->GetManifold()->localNormal.y));
	}

	void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{

	}

	void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{

	}

}