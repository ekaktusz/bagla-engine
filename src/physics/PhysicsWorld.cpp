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
	_world = std::make_unique<b2World>(b2Vec2(.0f, -40.f));
	_world->SetContactListener(&_contactListener);
}

void PhysicsWorld::cleanUp()
{
	for (auto* body : _bodiesToDestroy)
	{
		_world->DestroyBody(body->_body);
		delete body;
	}
	_bodiesToDestroy.clear();
}

void PhysicsWorld::update(const sf::Time& dt)
{
	static constexpr float timeStep = 1.0f / 60.0f;
	static constexpr int32 velocityIterations = 8;
	static constexpr int32 positionIterations = 3;
	_world->Step(timeStep, velocityIterations, positionIterations);

	for (auto* body : _bodiesToDestroy)
	{
		_world->DestroyBody(body->_body);
		delete body;
	}
	_bodiesToDestroy.clear();
}

void PhysicsWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (_debugDraw != nullptr)
		_world->DebugDraw();
}

void PhysicsWorld::initDebugDraw(sf::RenderWindow& renderWindow)
{
	_debugDraw = std::make_unique<DebugDraw>(renderWindow);
	_world->SetDebugDraw(&*_debugDraw);
	_debugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit);
}

void PhysicsWorld::destroyRigidBody(bgl::RigidBody* body)
{
	_bodiesToDestroy.push_back(body);
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