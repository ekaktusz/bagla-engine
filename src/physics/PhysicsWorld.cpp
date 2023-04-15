#include "physics/PhysicsWorld.h"

namespace bgl
{
	PhysicsWorld::~PhysicsWorld()
	{

	}

	PhysicsWorld::PhysicsWorld()
	{
		m_World = std::make_unique<b2World>(b2Vec2(.0f, -40.f ));
		m_World->SetContactListener(&m_ContactListener);
	}

	void PhysicsWorld::update(const sf::Time& dt)
	{
		static constexpr float timeStep = 1.0f / 60.0f;
		static constexpr int32 velocityIterations = 8;
		static constexpr int32 positionIterations = 3;
		m_World->Step(timeStep, velocityIterations, positionIterations);
	}
}