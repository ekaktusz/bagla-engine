#include "physics/RigidBody.h"

#include <box2d/b2_body.h>
#include <box2d/b2_world.h>

namespace bgl
{
	static constexpr float PPM = 32.f;

	RigidBody::RigidBody(float x, float y, float sx, float sy, b2World& world, bool dynamic /*= true*/)
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
		m_Fixture = m_Body->CreateFixture(&m_Shape, 1.0);
		m_Body->SetFixedRotation(true);
	}

	RigidBody::RigidBody(sf::Vector2f position, sf::Vector2f size, b2World& world, bool dynamic /*= true*/) : RigidBody(position.x, position.y, size.x, size.y, world, dynamic)
	{
		
	}


	RigidBody::~RigidBody()
	{

	}

	sf::Vector2f RigidBody::getPosition() const
	{
		float x = m_Body->GetPosition().x * PPM;
		float y = -m_Body->GetPosition().y * PPM;
		return sf::Vector2f(x - m_RigidBodyRectangleShape.getSize().x / 2, y - m_RigidBodyRectangleShape.getSize().y / 2);
	}

}