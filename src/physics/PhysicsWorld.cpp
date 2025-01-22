#include "physics/PhysicsWorld.h"
#include "physics/RigidBody.h"
#include <box2d/b2_draw.h>
#include <box2d/b2_math.h>
#include <box2d/b2_types.h>
#include <box2d/b2_world.h>
#include <memory>

namespace bgl
{

PhysicsWorld::PhysicsWorld()
{
	m_World = std::make_unique<b2World>(b2Vec2(.0f, -40.f));
	m_World->SetContactListener(&m_ContactListener);
}

void PhysicsWorld::cleanUp() 
{
	for (auto* body : m_BodiesToDestroy)
	{
		m_World->DestroyBody(body->m_Body);
		delete body;
	}
	m_BodiesToDestroy.clear();
}

void PhysicsWorld::update(const sf::Time& dt)
{
	static constexpr float timeStep = 1.0f / 60.0f;
	static constexpr int32 velocityIterations = 8;
	static constexpr int32 positionIterations = 3;
	m_World->Step(timeStep, velocityIterations, positionIterations);

	for (auto* body : m_BodiesToDestroy)
	{
		m_World->DestroyBody(body->m_Body);
		delete body;
	}
	m_BodiesToDestroy.clear();
}

void PhysicsWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_DebugDraw != nullptr)
		m_World->DebugDraw();
}

void PhysicsWorld::initDebugDraw(sf::RenderWindow& renderWindow)
{
	m_DebugDraw = std::make_unique<DebugDraw>(renderWindow);
	m_World->SetDebugDraw(&*m_DebugDraw);
	m_DebugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit);
}

void PhysicsWorld::destroyRigidBody(bgl::RigidBody* body)
{
	m_BodiesToDestroy.push_back(body);
}

bgl::RigidBody* PhysicsWorld::newRigidBody(float x, float y, float sx, float sy, bool dynamic /*= true*/, float density /*= 0.f*/)
{
	return new bgl::RigidBody(x, y, sx, sy, dynamic, density);
}

bgl::RigidBody* PhysicsWorld::newRigidBody(sf::Vector2f position, sf::Vector2f size, bool dynamic /*= true*/, float density /*= 0.f*/)
{
	return new bgl::RigidBody(position, size, dynamic, density);
}

float PhysicsWorld::scaleToGraphics(float f)
{
	return f * PIXEL_PER_METER;
}

sf::Vector2f PhysicsWorld::scaleToGraphics(b2Vec2 coordinates)
{
	return { scaleToGraphics(coordinates.x), scaleToGraphics(coordinates.y) };
}

float PhysicsWorld::scaleToPhysics(float f)
{
	return f / PIXEL_PER_METER;
}

b2Vec2 PhysicsWorld::scaleToPhysics(sf::Vector2f coordinates)
{
	return { scaleToPhysics(coordinates.x), scaleToPhysics(coordinates.y) };
}

}