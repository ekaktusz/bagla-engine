#include "physics/RigidBody.h"

#include "physics/PhysicsWorld.h"

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>
#include <box2d/box2d.h>

namespace bgl
{
static constexpr float PPM = 32.f;

RigidBody::RigidBody(float x, float y, float sx, float sy, bool dynamic /*= true*/, float density)
{
	initialize(x, y, sx, sy, dynamic, density);
}

RigidBody::RigidBody(sf::Vector2f position, sf::Vector2f size, bool dynamic /*= true*/, float density) :
	RigidBody(position.x, position.y, size.x, size.y, dynamic, density)
{
	initialize(position.x, position.y, size.x, size.y, dynamic, density);
}

void RigidBody::initialize(float x, float y, float sx, float sy, bool dynamic /*= true*/, float density /*= 0.f*/)
{
	_rigidBodyRectangleShape.setSize({ sx, sy });
	_rigidBodyRectangleShape.setPosition(x, y);
	_rigidBodyRectangleShape.setFillColor(sf::Color::Green);

	if (dynamic)
		_bodyDef.type = b2_dynamicBody;

	float bx = PhysicsWorld::scaleToPhysics(x + sx / 2);
	float by = -PhysicsWorld::scaleToPhysics(y + sy / 2);
	_bodyDef.position.Set(bx, by);
	_shape.SetAsBox(PhysicsWorld::scaleToPhysics(sx) / 2, PhysicsWorld::scaleToPhysics(sy) / 2);

	_body = PhysicsWorld::getInstance()._world->CreateBody(&_bodyDef);

	b2FixtureDef fixtureDef;
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	fixtureDef.shape = &_shape;
	fixtureDef.density = density;

	_fixture = _body->CreateFixture(&fixtureDef);
	_body->SetFixedRotation(true);
}

sf::Vector2f RigidBody::getPosition() const
{
	float x = PhysicsWorld::scaleToGraphics(_body->GetPosition().x);
	float y = -PhysicsWorld::scaleToGraphics(_body->GetPosition().y);
	return sf::Vector2f(x - _rigidBodyRectangleShape.getSize().x / 2, y - _rigidBodyRectangleShape.getSize().y / 2);
}

void RigidBody::setPosition(sf::Vector2f position)
{
	_body->SetTransform(PhysicsWorld::scaleToPhysics({ position.x, -position.y }), _body->GetAngle());
}

void RigidBody::setPosition(float x, float y)
{
	setPosition({ x, y });
}

sf::Vector2f RigidBody::getSize() const
{
	return _rigidBodyRectangleShape.getSize();
}

void RigidBody::setSize(float sx, float sy)
{
	float density = _fixture->GetDensity();
	_body->DestroyFixture(_fixture);
	initialize(getPosition().x, getPosition().y, sx, sy, _bodyDef.type == b2_dynamicBody, density);
}

void RigidBody::setLinearVelocity(sf::Vector2f velocity)
{
	_body->SetLinearVelocity(PhysicsWorld::scaleToPhysics({ velocity.x, velocity.y }));
}

void RigidBody::setLinearVelocity(float vx, float vy)
{
	_body->SetLinearVelocity(PhysicsWorld::scaleToPhysics({ vx, vy }));
}

void RigidBody::setGravityScale(float gravityScale)
{
	_body->SetGravityScale(gravityScale);
}

void RigidBody::setBeginContact(std::function<void(RigidBody*, sf::Vector2f)> beginContact)
{
	_beginContact = beginContact;
}

void RigidBody::setEndContact(std::function<void(RigidBody*, sf::Vector2f)> endContact)
{
	_endContact = endContact;
}

void RigidBody::setSensor(bool sensor)
{
	_fixture->SetSensor(sensor);
}

void RigidBody::beginContact(RigidBody* other, sf::Vector2f collisionNormal)
{
	if (_beginContact)
	{
		_beginContact(other, collisionNormal);
	}
}

void RigidBody::endContact(RigidBody* other, sf::Vector2f collisionNormal)
{
	if (_endContact)
	{
		_endContact(other, collisionNormal);
	}
}

const std::any& RigidBody::getUserCustomData() const
{
	return _userCustomData;
}

void RigidBody::setUserCustomData(const std::any& userCustomData)
{
	_userCustomData = userCustomData;
}

}