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
	m_RigidBodyRectangleShape.setSize({ sx, sy });
	m_RigidBodyRectangleShape.setPosition(x, y);
	m_RigidBodyRectangleShape.setFillColor(sf::Color::Green);

	if (dynamic)
		m_BodyDef.type = b2_dynamicBody;

	float bx = PhysicsWorld::scaleToPhysics(x + sx / 2);
	float by = -PhysicsWorld::scaleToPhysics(y + sy / 2);
	m_BodyDef.position.Set(bx, by);
	m_Shape.SetAsBox(PhysicsWorld::scaleToPhysics(sx) / 2, PhysicsWorld::scaleToPhysics(sy) / 2);

	m_Body = PhysicsWorld::getInstance().m_World->CreateBody(&m_BodyDef);

	b2FixtureDef fixtureDef;
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	fixtureDef.shape = &m_Shape;
	fixtureDef.density = density;

	m_Fixture = m_Body->CreateFixture(&fixtureDef);
	m_Body->SetFixedRotation(true);
}

sf::Vector2f RigidBody::getPosition() const
{
	float x = PhysicsWorld::scaleToGraphics(m_Body->GetPosition().x);
	float y = -PhysicsWorld::scaleToGraphics(m_Body->GetPosition().y);
	return sf::Vector2f(x - m_RigidBodyRectangleShape.getSize().x / 2, y - m_RigidBodyRectangleShape.getSize().y / 2);
}

void RigidBody::setPosition(sf::Vector2f position)
{
	m_Body->SetTransform(PhysicsWorld::scaleToPhysics({ position.x, -position.y }), m_Body->GetAngle());
}

void RigidBody::setPosition(float x, float y)
{
	setPosition({ x, y });
}

sf::Vector2f RigidBody::getSize() const
{
	return m_RigidBodyRectangleShape.getSize();
}

void RigidBody::setSize(float sx, float sy)
{
	float density = m_Fixture->GetDensity();
	m_Body->DestroyFixture(m_Fixture);
	initialize(getPosition().x, getPosition().y, sx, sy, m_BodyDef.type == b2_dynamicBody, density);
}

void RigidBody::setLinearVelocity(sf::Vector2f velocity)
{
	m_Body->SetLinearVelocity(PhysicsWorld::scaleToPhysics({ velocity.x, velocity.y }));
}

void RigidBody::setLinearVelocity(float vx, float vy)
{
	m_Body->SetLinearVelocity(PhysicsWorld::scaleToPhysics({ vx, vy }));
}

void RigidBody::setGravityScale(float gravityScale)
{
	m_Body->SetGravityScale(gravityScale);
}

void RigidBody::setBeginContact(std::function<void(RigidBody*, sf::Vector2f)> beginContact)
{
	m_BeginContact = beginContact;
}

void RigidBody::setEndContact(std::function<void(RigidBody*, sf::Vector2f)> endContact)
{
	m_EndContact = endContact;
}

void RigidBody::setSensor(bool sensor)
{
	m_Fixture->SetSensor(sensor);
}

void RigidBody::beginContact(RigidBody* other, sf::Vector2f collisionNormal)
{
	if (m_BeginContact)
	{
		m_BeginContact(other, collisionNormal);
	}
}

void RigidBody::endContact(RigidBody* other, sf::Vector2f collisionNormal)
{
	if (m_EndContact)
	{
		m_EndContact(other, collisionNormal);
	}
}

const std::any& RigidBody::getUserCustomData() const
{
	return m_UserCustomData;
}

void RigidBody::setUserCustomData(const std::any& userCustomData)
{
	m_UserCustomData = userCustomData;
}

}