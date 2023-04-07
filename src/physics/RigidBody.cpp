#include "physics/RigidBody.h"

#include <box2d/b2_body.h>
#include <box2d/b2_world.h>
#include <box2d/box2d.h>

namespace bgl
{
	static constexpr float PPM = 32.f;

	RigidBody::RigidBody(float x, float y, float sx, float sy, b2World& world, bool dynamic /*= true*/, float density) : m_World(world)
	{
		m_RigidBodyRectangleShape.setSize({sx, sy});
		m_RigidBodyRectangleShape.setPosition(x, y);
		m_RigidBodyRectangleShape.setFillColor(sf::Color::Green);

		if (dynamic) m_BodyDef.type = b2_dynamicBody;

		float bx = (x + sx / 2) / PPM;
		float by = -(y + sy / 2) / PPM;
		m_BodyDef.position.Set(bx, by);
		m_Shape.SetAsBox(sx / PPM / 2, sy / PPM / 2);

		m_Body = world.CreateBody(&m_BodyDef);

		b2FixtureDef fixtureDef;
		//  (uintptr_t) this;
		fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
		fixtureDef.shape = &m_Shape;
		fixtureDef.density = density;

		m_Fixture = m_Body->CreateFixture(&fixtureDef);
		m_Body->SetFixedRotation(true);
		
	}

	RigidBody::RigidBody(sf::Vector2f position, sf::Vector2f size, b2World& world, bool dynamic /*= true*/, float density) : RigidBody(position.x, position.y, size.x, size.y, world, dynamic, density)
	{
		
	}


	RigidBody::~RigidBody()
	{
		m_Body->DestroyFixture(m_Fixture);
		m_World.DestroyBody(m_Body);
	}

	sf::Vector2f RigidBody::getPosition() const
	{
		float x = m_Body->GetPosition().x * PPM;
		float y = -m_Body->GetPosition().y * PPM;
		return sf::Vector2f(x - m_RigidBodyRectangleShape.getSize().x / 2, y - m_RigidBodyRectangleShape.getSize().y / 2);
	}

	void RigidBody::setLinearVelocity(sf::Vector2f velocity)
	{
		m_Body->SetLinearVelocity({ velocity.x, velocity.y });
	}

	void RigidBody::setGravityScale(float gravityScale)
	{
		m_Body->SetGravityScale(gravityScale);
	}
}